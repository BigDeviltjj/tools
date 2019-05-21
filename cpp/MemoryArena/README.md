### MemoryArena

This is a memory allocation wrapper library copied from[pbrt-v3](https://github.com/mmp/pbrt-v3).

In the case of dynamic individual class objects, it is preferable.

It is better than conventional ```new, delete``` in to aspects:

1. It allocates aligned memory which increases memory access speed.

2. It preallocates a large amount of continuous memory, so that in the cases of successive allocation of small piece of memory, it is more efficient.

### Tips

1. alloca can allocate stack memory which can be recycled automatically, it is much faster than malloc. Also, you are more prone to contact with stackoverflow.

2. using valgrind to check memory leak of your program

```
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./useMemory
```

For macOS Mojave(10.14) users, checkout [here](https://stackoverflow.com/questions/52732036/how-to-install-valgrind-on-macos-mojave10-14-with-homebrew)
for installation issues.


