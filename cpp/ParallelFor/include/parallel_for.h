#ifndef PARALLEL_FOR_H
#define PARALLEL_FOR_H
#include <functional>
bool ParallelFor(std::function<void(int64_t)> f, int a, int b, int chunkSize = 64);
#endif
