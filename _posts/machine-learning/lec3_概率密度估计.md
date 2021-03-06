朴素贝叶斯分类器（Naive Bayesian Classifier）

限制条件：① 向量 X 的每个维度都是离散的

② X 的每个维度都是独立的（都不相关）

假设有个应用叫垃圾邮件分类，跟一个文件，只分两类（是否是垃圾邮件）。

输入：一个邮件 d

输出：d in c_1 或 d in c_2

训练样本 {(d_i, y_I)}_{i=1-N}，d={w1, w2, ..., wn} （每个邮件的特征）

学习目标：P(d|c_1) 和 P(d|c_2)

P(d|C) = P({w1, w2, ..., wn} | C)

考虑两个限制条件，对于限制条件 ①，w 在这里被理解为单词，单词虽然很多，但他的数目是有限的，因此可以被离散表示。对于限制条件 ②，显然不是独立的，因为单词与单词之间存在语义关系。但是在垃圾邮件分类这一简单的任务里，可以假设 ②成立，在一些较为复杂的比如语音识别，便不可这么做。

P(d|C) = P({w1, w2, ..., wp} | C) = [累乘 i in n]P(w_i|C)

P(w_i|C_j) = count(w_i, c_j) / [累加w in V]count(w, c_j)，其中 j=1-2。

P(C_i) = count(C_i) / count(C)

 若P(d|c_1)P(c_1) > P(d|c_2)P(c_2) 则 d in c_1。

但可能存在例外情况，考虑一个单词未在训练集中出现过，那么 P(d|c) [不管c取哪个] 都是 0。为防止这种情况，改进计算公式如下：

P(w_i|C_j) = count(w_i, c_j) + 1/ [累加w in V]count(w, c_j) + |V|，其中 j=1-2。



高斯密度函数

假设 {x_i}_{i=1-n} in C，X_i 是一维情况：

$P(X|C) = \frac{1}{\sqrt{2\pi \sigma}}e ^ {- \frac{(x-\mu)^2}{2\sigma^2}}$ 

$\mu = \frac{1}{N} \sum^{N}_{i=1}X_i$

$\sigma^2=\frac{1}{N-1}\sum^{N}_{i=1}(X_i-\mu)^2$ [无偏估计]

这个是一维的情况，尝试证明高维的情况，

$P(X|C)=\frac{1}{\sqrt{(2\pi)^d |\sum|}}exp[-\frac{1}{2}(x-\mu)^T\sum^{-1}(x-\mu)]$

带求参数 $\sum $ 和 $\mu$。利用极大似然法，构造目标函数：

$E(\mu, \sum)=\sum^{N}_{i=1}lnP(x_i|C)$

基于假设：① 所有 {X_i}_{i=1-N}  独立同分布

② 设定 $\mu$ ，$\sum$ 使出现 {x_i} 的概率最大。

化简，具体的证明课后去了解。

<img src="https://s2.loli.net/2022/06/04/OLDuRB6bo7gFwHi.png" alt="image-20220604170701333" style="zoom:50%;" />

在这里要强调几点，做概率分类法要留意的几点：

① 假设 X 的概率分布的具体形式。也即假设 P(X|C)，在这个具体形式当中，有一些待定参数，例如高斯概率分布中为 $\mu, \sum$。

② 用极大概率似然法构造优化目标函数。

③ 解 ② 中的优化问题，获得待求参数。

当然，由于高斯函数是个凸的函数，极大值就是全局最大值，以至于可以直接用微分求出。但是在很多情况下是算不出来的，那这么做呢？可以梯度下降等等。



高斯混合模型

最后，举例构造一个算不出来的最值的问题。也即混合高斯模型（Gaussian Mixture Model）。

![image-20220604171707303](https://s2.loli.net/2022/06/04/wR7JIZ2tYvSeybK.png)

![image-20220604172023016](https://s2.loli.net/2022/06/04/1KW7LlMsoDGmIVY.png)



