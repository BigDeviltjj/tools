#ifndef MY_UTILS_H
#define MY_UTILS_H
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <unordered_map>
#include <set>
#include <map>
#include <functional>
#include <string>

#define PROC(v, func) std::for_each(v.begin(), v.end(), func);
#define rPROC(v, func) std::for_each(v.rbegin(), v.rend(), func);

template<typename FunctionType>
void testTime(FunctionType f, std::string mesg) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<"duration of "<<mesg<<" : "<<duration.count()<<std::endl;
}
#endif
