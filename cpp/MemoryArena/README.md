### MemoryArena

This is a memory allocation wrapper library copied from[pbrt-v3](https://github.com/mmp/pbrt-v3).

In the case of dynamic individual class objects, it is preferable.

It is better than conventional ```new, delete``` in to aspects:

1. It allocates aligned memory which increases memory access speed.

2. It preallocates a large amount of continuous memory, so that in the cases of successive allocation of small piece of memory, it is more efficient.

### Tips

1. alloca can allocate stack memory which can be recycled automatically, it is much faster than malloc. Also, you are more prone to contact with stackoverflow.

