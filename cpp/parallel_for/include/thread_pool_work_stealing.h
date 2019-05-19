#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

#include "queue_work_stealing.h"
#include "threadsafe_queue.h"

class join_threads
{
    std::vector<std::thread> &threads;
public:
    explicit join_threads(std::vector<std::thread> &threads_):
        threads(threads_)
    {}
    ~join_threads()
    {
        for(unsigned long i = 0; i < threads.size(); ++i)
        {
            if (threads[i].joinable())
                threads[i].join();
        }
    }
};


class thread_pool
{
    typedef function_wrapper task_type;
    std::atomic_bool done;
    std::vector<std::thread> threads;
    threadsafe_queue<task_type> pool_work_queue;
    std::vector<std::unique_ptr<work_stealing_queue>> queues;
    join_threads joiner;

    static thread_local work_stealing_queue *local_work_queue;
    static thread_local unsigned my_index;

    // worker thread 在开始时调用一次，传入其idx，每运行一次产生他的local_work_queue
    void worker_thread(unsigned my_index_)
    {
        my_index = my_index_;
        local_work_queue = queues[my_index].get();
        while (!done)
        {
            run_pending_task();
        }
    }
    // 各个线程自己的queue
    bool pop_task_from_local_queue(task_type &task)
    {
        return local_work_queue && local_work_queue->try_pop(task);
    }

    // 主线程的queue
    bool pop_task_from_pool_queue(task_type &task)
    {
        return pool_work_queue.try_pop(task);
    }
    bool pop_task_from_other_thread_queue(task_type &task)
    {
        for (unsigned i = 0; i < queues.size(); ++i)
        {
            unsigned const index = (my_index+i+1)%queues.size();
            if (queues[index]->try_steal(task))
            {
                return true;
            }
        }
        return false;
    }

public:

    // joiner 的成员变量是个threads的引用
    thread_pool():
        done(false), joiner(threads)
    {
        unsigned const thread_count = std::thread::hardware_concurrency();
        try
        {
            // 生成cnt个线程和queue
            for (unsigned i = 0; i < thread_count; ++i)
            {
                queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
            }


            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads.push_back(
                        std::thread(&thread_pool::worker_thread, this, i));
            }
        }
        catch(...)
        {
            done = true;
            throw "an error occured!\n";
        }
    }
    ~thread_pool()
    {
        done = true;
        joiner.~join_threads();
    }

    // FunctionType 是一个bind类型的函数
    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
    submit(FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type result_type;
        // 斜括号中的类型为<ret(param)> 由于bind输入为空，所以中间无内容
        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        if (local_work_queue)
        {
            local_work_queue->push(std::move(task));
        }
        else{
            // 只会对父线程i起作用
            pool_work_queue.push(std::move(task));
        }
        return res;
    }

    void run_pending_task()
    {
        task_type task;
        if(pop_task_from_local_queue(task) ||
           pop_task_from_pool_queue(task) ||
           pop_task_from_other_thread_queue(task))
        {
            task();
        }
        else
        {
            // 将运行还给别人
            std::this_thread::yield();
        }
    }
};
thread_local work_stealing_queue *thread_pool::local_work_queue;
thread_local unsigned thread_pool::my_index;

