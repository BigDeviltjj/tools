### Profiling PyTorch code

* The goal of profiling is to find the bottleneck ,in other words, the most time-consuming part, of existing code for speeding up your code.

* cProfile is a python’s module for profiling code.

* you can use cProfile in python code like following:

```
import cProfile

def Foo(args):

    # run your code
    pass

# following usage will print running time of functions on std output.

cProfile.run("Foo(args)")

# following usage will print running time of functions to specified file.

cProfile.run("Foo(args)", filename="Foo.prof")
```

* if you want to profile the whole program, use following command:

```
python -m cProfile -o Foo.prof Foo.py
```

* to visualize output file "Foo.prof", run following command. If you are on server, run `snakeviz -H 0.0.0.0 Foo.prof`, than change 0.0.0.0 to server ip in opened browser.

```
pip install snakeviz
snakeviz Foo.prof
```


### Note!!!(for pytorch)

In pytorch, CUDA code is asynchronous by default, leading to incorrect function running time. To make CUDA functions synchronized, set environment variable `CUDA_LAUNCH_BLOCKING=1`. For example
```
CUDA_LAUNCH_BLOCKING=1 python -m cProfile -o Foo.prof test_net.py  --config-file configs/e2e_point_rcnn_scannet_rcnn.yaml
```

By setting `CUDA_LAUNCH_BLOCKING=1`, CUDA kernels which are ought to be added into running queue by CUDA stream will run immediately.
For more information about above information, I strongly recommend following reference:

[CUDA by example](http://www.mat.unimi.it/users/sansotte/cuda/CUDA_by_Example.pdf)(chapter 10)

Follwoing two official guides might also be helpful but personally I prefer the above one.

[cuda-c-programming-guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)

[cuda-c-best-practices-guide](https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/)

