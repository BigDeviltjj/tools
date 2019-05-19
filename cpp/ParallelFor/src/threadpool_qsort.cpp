#include <vector>
#include <numeric>
#include <iostream>
#include <list>
#include <algorithm>
#include "thread_pool.h"
template<typename T>
struct sorter
{
    thread_pool pool;
    std::list<T> do_sort(std::list<T> &chunk_data)
    {
        std::cout<<chunk_data.size()<<std::endl;
        if (chunk_data.empty())
        {
            return chunk_data;
        }
        std::list<T> result;
        // a.splice(iter(a), b, iter(b)): 将iter(b)放在iter(a)前面, 同时删除b中iterator
        result.splice(result.begin(), chunk_data, chunk_data.begin());
        T const &partition_val = *result.begin();
        // v::iterator p = partition(b, e, cmp);  返回第一个不满足cmp的iter 
        typename std::list<T>::iterator divide_point =
		        std::partition(chunk_data.begin(),chunk_data.end(),
		        [&](T const& val){return val<partition_val;});
        std::list<T> new_lower_chunk;
        new_lower_chunk.splice(new_lower_chunk.end(), chunk_data,chunk_data.begin(), divide_point);
        // 新开一个线程处理do_sort，用bind解决传参问题, future 接受返回参数
	      std::future<std::list<T>> new_lower = 
		        pool.submit(std::bind(&sorter::do_sort, this, std::move(new_lower_chunk)));
        // higher 还是在主线程处理
	      std::list<T> new_higher(do_sort(chunk_data));
	      result.splice(result.end(), new_higher);
        // 直到new_lower的状态是ready 才返回
      	while(!(new_lower.wait_for(std::chrono::seconds(0)) == 
      		std::future_status::ready))
      	{
            // 在主线程中调用run_pending_task();
      	    pool.run_pending_task();
      	}
        // 合并
      	result.splice(result.begin(), new_lower.get());
      	return result;
    }
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    sorter<T> s;
    return s.do_sort(input);
}

int main() {
    std::vector<int> v(100);
    // iota v[i] = val++;
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());
    std::list<int> a(v.begin(), v.end());
    std::for_each(a.begin(), a.end(), [](int i) {std::cout<<i<<" ";});
    std::cout<<std::endl;
    a = parallel_quick_sort(a);
    for (auto &i : a) {
        std::cout<<i<<" "<<std::endl;
    }
    return 0;
}

