### parallel toolkit based on c++11 thread

---

### usage

1. ParallelFor

```
ParallelFor(func, start, end, chunkSize=64)
```

This api equals to parallel version of 

```
for (int64_t i = start; i < end; ++i) {
    func(i);
}
```

you have to add ```include``` and ```bin``` for header file and .so file respectively.


2. class ```thread_pool```. The class implements thread safe thread pool function with feature work stealing to achieve better parallelism. 
Typial usage can be found in ```threadpool_qsort.cpp```. For common users, it is called like bellow:

```
#include "thread_pool.h"  // "thread_pool_work_stealing.h" performs better when threads calls sub threads, but its name is too long
...
trhead_pool tp;
auto ret = tp.submit(std::bind(func));
cout<<ret.get()<<endl;
...
```
This class only has header file.

---

### develop log

#### issue 1. 

我开始花了很多时间开发一个可以传入包含任何参数的函数的feature, 具体可见[函数调用与右值引用](https://zhuanlan.zhihu.com/p/50673895)。 
后来发现只需要将传入的函数用bind封装一下即可。


#### issue 2. 

写ParallelFor代码时总是调试出错，后来发现即使传入没有返回的function也需要调用get，这个内部和异步运算有关，feature<T>::get()类似于thread::join的功能，不能忽略

#### issue 3.

issue 2调出来后发现还是经常退出异常，报错unlock()失败。调试发现众所周知（个屁），
编译器会偷偷的在C++类构造函数的最开始/析构函数最后面调用成员变量的构造/析构函数，其调用顺序与成员变量的定义相同（构造）/相反（析构）。
因此
```
std::vector<std::thread> threads;
join_threads joiner;
```
这两行顺序不能变，必须先析构joiner调用join_threads的析构函数，再销毁threads中的thread对象，否则thread被销毁了joiner还在判断joinable报错。

#### issue 3.

上面bug修正后又发现```thread_pool_work_stealing```总是不能正常构造，一通debug发现这与编译器优化有关
```
for (unsigned i = 0; i < thread_count; ++i)
{
    queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
}


for (unsigned i = 0; i < thread_count; ++i)
{
    threads.push_back(
            std::thread(&thread_pool::worker_thread, this, i));
}
```
两个push_back不可以写在同一个循环里，否则无法保证其执行顺序，需要将其定义为```volatile```，可是这个涉及到内存模型需要花大量时间重构（其实就是不会），
所以干脆分成两个for循环执行保证其正确.

