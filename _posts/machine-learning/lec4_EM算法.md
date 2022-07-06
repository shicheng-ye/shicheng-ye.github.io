

## <center>EM（Expectation-Maximization）算法</center>

### 1. 简介

求局部极值的算法，只对某一类局部极值问题可解。

优点：① 不需要调任何参数 ② 编程简单

问题：如果我们知道每一个点归属于哪个高斯分布，那么我们能够容易地估计每个高斯分布的均值和方差。但问题是我们不知道每一个点归属于哪个高斯分布。如何来打破？EM算法。



### 2. GMM 中的 EM

① 先做随机化假设：要么 a. 随机化每一个点的分布归属，要么 b. 随机化高斯分布的参数

以 b. 为例，然后算出点的归属，然后再算高斯分布的参数。

② E-step：

![image-20220606100216870](https://s2.loli.net/2022/06/06/Gysjb84E7Apgclx.png)

③ M-step：

![image-20220606100550644](https://s2.loli.net/2022/06/06/2ascSdWmEr67wA9.png)

④ 回到 ②，不断循环，直到收敛。



### 3. K-Means 中的 EM

再看另一个 EM 算法的例子 —— K-means。

无监督学习的一种。

问题：输入 N 个样本 {X_i}\_{i=1-N}，输出 N 个样本的类别 {Z_i}\_{i=1-N}。

![image-20220606101157744](https://s2.loli.net/2022/06/06/mb9ogI1siFK4Lln.png)

证明 k-means 算法：

首先定义这样一个目标函数：

![image-20220606101527303](https://s2.loli.net/2022/06/06/hJnb35HdoOpcmfj.png)

然后看第 ② 步，经过第 ② 步，会使得 E 减小。

再考虑第 ③ 步， 由于存在以下情况：

![image-20220606101830189](https://s2.loli.net/2022/06/06/j7TQNYWmxbE4hAO.png)

因此，第 ③ 步的均值调整方法也会让 E 变小。综上，而 E 下界 0，又因存在一个 序列 使得 E 单调下降，故 E 一定收敛。



### 4. EM 算法一般形式

根据以上例子，得出 EM 算法的一般形式。给定已知的联合分布：
$$
p(x,z;\theta)
$$
其中，x 是观察到的变量，z 是潜在变量，我们要做的是最大化如下的对数最大似然估计：
$$
\theta = argmax_{\theta}logp(x;\theta)\\
p(x;\theta) = \sum_{z}p(x,z;\theta)
$$
高斯混合模型中的隐含变量：每个点属于某个高斯分布的概率

K-Means 中的隐含变量：每个点是否属于某个聚类

![image-20220607200553293](https://s2.loli.net/2022/06/07/UgaT2WLBPjD8cGk.png)

同乘同除等价

根据 Jensen 不等式推导：在这里，f(x) = logx；E(x) = log[] 方括号内的东西，那么 X 就是那个分式。

![image-20220607201340238](https://s2.loli.net/2022/06/07/s1lUNEP4jqkG5ST.png)

最后一行理解为：让下界等价于 E(theta)，这样就完成了等式的推导。也即是说，在等价的情况下，最大化这个下界就是最大化对数似然函数了。

最后一行的推导如下：

![image-20220607203857799](https://s2.loli.net/2022/06/07/qpMyfvmV84D52jC.png)

通过 E 步，找到了使得等号成立的 $Q_i(z^{(i)})$。这样以后，我们就可以最大化 E(f(x)) 了，也即是等价于最大化 f(E(x))。

基于以上推导，得到 EM 算法的一般形式。

![image-20220607203956530](https://s2.loli.net/2022/06/07/dkWnjMyzvGBDwbI.png)

之后便可证明

![image-20220607205107298](https://s2.loli.net/2022/06/07/XKRqbY4rVck8wJQ.png)



接下来讨论一般的 EM 算法与 kmeans 算法的关联。

z_i 的定义：点 i 属于哪个聚类。

为什么 p 这么定义？

![image-20220607205447457](https://s2.loli.net/2022/06/07/UigG9DXkeLtv5Zh.png)

最后一行等式是求导

![image-20220607210820263](https://s2.loli.net/2022/06/07/y2CeMFlgcnTLkA6.png)

之后对其求微分：

![image-20220607212116393](https://s2.loli.net/2022/06/07/blL2e59Ak3fDtRx.png)

总结特点：初值选择不好会导致不好的结果；能收敛；局部极值。



参考资料：

https://blog.csdn.net/Matrix_cc/article/details/105266141

