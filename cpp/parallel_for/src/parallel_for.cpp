#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>

#include "thread_pool_work_stealing.h"
std::atomic<int> sum(0);

void loop(std::function<void(int64_t)> f, int a, int b) {
  for (int i = a; i< b; ++i) {
    f(i);
  }
}
bool ParallelFor(std::function<void(int64_t)> f, int a, int b, int chunkSize = 64) {
  thread_pool tp;
  std::vector<std::future<void>> res;
  while (a < b) {
    int nextStep = a + chunkSize <= b ? a + chunkSize: b;
    res.push_back(tp.submit(std::bind(loop, f, a, nextStep)));
    a += chunkSize;
  }
  std::for_each(res.begin(), res.end(), [](std::future<void> &i) {i.get();});
  return true;
}
