### Geometry

It is perferable to utilize [eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) or [mshadow](https://github.com/dmlc/mshadow) in practice.

The goal of this repository is to illustrate some important optimize technologies used in Geometry librarie. I will also record algebra programming issues I found and resolved.

### TODO

* []  add CRTP
* []  add template expression 



### Issues

1. rotation matrix have to satisfy 
  1. $\mathbf{R}^T\mathbf{R}=\mathbf{I}$ 

    since it is composed of three orthogonal normalized vectors.

  2. $\mathrm{det}(\mathbf{R})=1$
    
    since if $\mathbf{R}$ rotates $\mathbf{v}$ to $\mathbf{w}$, then we have
      
    $
    ||\mathbf{Rv}||_2=||\mathbf{w}||_2
    $

    for all $\mathbf{v}$, suppose $\mathbf{v}=\mathbf{p}$ where $\mathbf{p_i}$ is the $i$th eigenvector of $\mathbf{R}$, then

    $\begin{align*}
    ||\mathbf{Rp}||_2&=||\lambda\mathbf{p}||_2 \\
    &=\lambda||\mathbf{p}||_2 \\
    &=||\mathbf{p}||_2 \\
    \end{align*}$

    Thus, all eigenvalues satisfy $\lambda=1$, and then 

    $\mathrm{det}(\mathbf{R})=1$

    Another way to justify this is $\mathbf{R}$ is continuous over time, then 

    $\mathbf{R}(0)=\mathbf{I}, \mathrm{det}(\mathbf{R})=1$
