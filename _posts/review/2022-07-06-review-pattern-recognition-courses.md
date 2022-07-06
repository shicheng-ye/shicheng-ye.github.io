---
layout: post
title:  "[review]Pattern recognition courses"
date:   2022-07-06 15:09:45 +0800
categories: courses
---



### 1. 总览

<img src="https://s2.loli.net/2022/06/25/NcpDeYXjQLCB7wb.png" alt="image-20220625120156682" style="zoom: 67%;" />

**考核形式**

主要考对概念的一些理解，例如说偏置方差分解和过拟合欠拟合之间的关系

计算有但不是太多

在理解的基础上对算法进行记忆，比如 PCA & LDA，他们的目标函数优化这些都是要知道的



### 2. 提取特征

> 提取特征：Normalization(Chap. 9), PCA(Chap. 5), FLD(Chap. 6), Sparse(Chap. 11), …
> PCA 无监督，FLD 有监督地利用标签去提取特征的方法
> Sparse 没有详细地去讲

#### Normalization

<img src="https://s2.loli.net/2022/06/25/Vu6rQ4LS8Rylxvb.png" alt="image-20220625122340062" style="zoom: 67%;" />

<img src="https://s2.loli.net/2022/06/25/OfLYdTHaN3JwQX8.png" alt="image-20220625122352658" style="zoom:67%;" />

可以把范围从 [0, 1] 拉伸至任意范围。

如果某一维度的最大值等于最小值，这个维度的数据可以丢掉。

如果 0 值在原始数据中代表 “空”，那么应该把它规范成0。

如果测试样例的数据范围大于 0 或 大于 1，有时候算法必须要求 [0, 1]，那么可以把小于 0 的值设为 0，大于 1 同理，如果算法不要求其实也可以这么做。

如果能看出某维数据符合高斯分布，那么也可以化为标准高斯分布：

<img src="https://s2.loli.net/2022/06/25/5P1Z49mjxLMqrBH.png" alt="image-20220625122726742" style="zoom: 67%;" />

L-1 规范化：如果值非负，规范化后样例各维之和为 1

<img src="https://s2.loli.net/2022/06/25/cNhxoSBs9TGaEyZ.png" alt="image-20220625122931565" style="zoom:67%;" />

L-2 规范化：把数据规范化为单位向量

<img src="https://s2.loli.net/2022/06/25/G9Fc2trETn1ZvoU.png" alt="image-20220625122925127" style="zoom:67%;" />

#### PCA

首先要会做 SVD 分解。

<img src="https://s2.loli.net/2022/06/25/Hn4AO2M1Ze8hL9v.png" alt="image-20220625155915036" style="zoom: 67%;" />

![image-20220625155923920](https://s2.loli.net/2022/06/25/3rj7boJ9OiTKktw.png)

#### FLD

思想：把数据点进行投影，使得不同类别之间的数据距离尽可能大。

 <img src="https://s2.loli.net/2022/06/25/oudrltBzY3psvSE.png" alt="image-20220625160821944" style="zoom: 50%;" />     <img src="https://s2.loli.net/2022/06/25/v5VHwi7oY9ELePM.png" alt="image-20220625162319955" style="zoom: 50%;" />

可分性的绝对要素：两个均值之间的距离 + 两个标准差。要实现分类，就需要最大化这二者的比例。

注：PCA 和 FLD 中的 X 的尺寸都是 (dim x 1) 。因而，$$a^Ta$$ 的结果是一个值，$$aa^T$$ 的结果是一个矩阵。

二分类的 FLD：

<img src="https://s2.loli.net/2022/06/25/1UghbLr4SEZizaY.png" alt="image-20220625165356810" style="zoom: 50%;" />

$$w$$：投影方向

$$m_i$$ ：集合 i 的均值

$$C_i$$ ：集合 i 的协方差矩阵

$$
C_i = \frac{1}{N_i} \sum_{x \in X_i} (x-m_i)(x-m_i)^T
$$

传统 FLD 用散度矩阵而不是用协方差矩阵，散度矩阵 $$S_i = N_iC_i$$

类间散度矩阵 & 类内散度矩阵：

$$
S_B=(m_1-m_2)(m_1-m_2)^T \\
S_W = S_1+S_2
$$

目标函数（第一行的 m 是投影后的均值，第二行的 m 是向量）：

$$
J = \frac{(m_1-m_2)^2}{\sigma_1^2+\sigma_2^2} \\
= \frac{(m_1^T w-m_2^Tw) ^ 2}{\sigma_1^2+\sigma_2^2} \\
= \frac{w^T(m_1-m_2)(m_1-m_2)^Tw}{w^T(C_1+C_2)w} \\
= \frac{w^TS_Bw}{w^TS_Ww} \\
$$

如果一个均值向量扮演了所属类别的所有样本的代理，那么就可以用均值向量集合的散度矩阵代替 $$S_B$$

$$
\sum^{2}_{i=1}(m_i - \overline{m})(m_i - \overline{m}) ^T \\
\overline{m} = \frac{m_1+m_2}{2}
$$

之后就可以计算以及规范化了。

考虑至多类别呢？

类内散度矩阵 

$$
S_W = \sum ^{K}_{k=1} S_k = \sum ^{K}_{k=1}N_kC_k = \sum ^{K}_{k=1} \sum_{x \ in X_k}(x-m_i)(x-m_i)^T
$$

总散度矩阵

$$
S_T = \sum ^{N}_{i=1}(x_i-m)(x_i-m)^T \\
m = \frac{1}{N} \sum^{N}_{i=1}x_i
$$

类间散度矩阵

$$
S_B =\sum ^{K}_{k=1}N_k(m_k-m)(m_k-m)^T
$$

规律：总散度矩阵 =  类内散度矩阵 + 类间散度矩阵。

多分类问题中，类间散度矩阵不再是秩为 1 的矩阵，算法 6.1 不可用，故求解如下广义特征值问题来找最佳投影方向：

$$
S_B w = \lambda S_W w
$$

当 $S_W$ 可逆，广义特征值问题等价于：

$$
S_W ^ {-1} S_B w = \lambda  w
$$

那么如何找更多投影方向（降低更多维度）呢？类似 PCA，只要使用与前 K-1 个最大广义特征值对应的广义特征向量即可

#### Sparse

含义：最小化 $$l_0$$$ norm（向量 x 的非零元素个数）

$$
minimize\  ||x||_0 \\
subject\ to\ Ax=y
$$




### 3. 分类器

>分类器：kNN, SVM, Decision Tree, Ensemble, Regression, NN, CNN
>kNN, SVM 前两个重要，后面都是简单提一下
>CNN 也可以看作是个特征提取的方法

#### kNN（机器学习）

理解且会用

缺陷以及解决办法

1. 出现平局：可以给不同的样本施加不同的权重，加强依赖样本的权重，降低不可信赖样本的影响。

2. 离群点

复杂度 O(nd) [d是计算距离的代价]

#### SVM（机器学习）

#### Decision Tree + Regression（机器学习）

#### Ensemble

#### NN

#### CNN



### 4. 概率模型

>概率模型 (Chap. 8)：参数估计，非参，HMM，GMM
>参数估计：点估计，贝叶斯估计，HMM
>非参数估计：KDE
>要知道 HMM 的隐马尔可夫性质 + 要知道 GMM 的概念

概率模型：计算变量的概率或者概率分布的模型。

参数估计：假设 PDF 服从某种函数形式，当指定其所有参数值之后，PDF 就完全确定，估计 PDF 就是估计参数。

非参数估计：非参数不代表无参数（允许无限），用训练数据直接估计空间中任意点的密度 p(x|D)。

生成模型：估计 p(x|y=i) 和 p(y=i)，根据贝叶斯定理求 p(y=i|x)

判别模型：直接估计 p(y=i|x)

这些模型都有两个步骤：推理和决策，分别是估计各种密度函数，根据估计得到的PDF对任意的？给出输出。

#### 点估计（参）

点估计（point estimation）是用样本统计量来估计总体参数，典型的如 MLE 和 MAP，把 $$\theta$$ 视作固定参数，目的是找这个最佳参数。

p(D|theta) 不是 PDF，但 p(x|theta) 是。

likelihood function of MLE：

$$
l(\theta) = p(D|\theta) = \prod_{i}p(x_i|\theta)
$$

高斯分布的最大似然估计，可以通过对 $ll(\theta)$ 求偏微分得到结果：

$$
\mu = \frac{1}{n} \sum^{n}_{i=1}x_i \\
\sigma^2 = \frac{1}{n} \sum^{n}_{i=1}(x_i-\mu)(x_i-\mu)^T 
$$

最大后验估计（MAP）：把参数 theta 自身的取值可能性考虑进来。如果一无所知就等价于 MLE。

$$
\theta = argmax_{\theta} l(\theta)p(\theta)
$$

渐进性质（asymptotic property），如一致性（consistency）：随样本容量增大收敛到参数真值的估计量

其他性质，无偏估计（unbiased estimate）：指估计量的期望和被估计量的真值相等

完成 inference 后，如何决策？根据参数得到后验概率 p(y|x;theta) 得出结果，在 0-1 风险时，选择概率大的就行。

<img src="https://s2.loli.net/2022/06/29/rTozyVmcjG6n1RC.png" alt="image-20220625193547900" style="zoom: 33%;" />

#### 贝叶斯估计（参）

点估计是把 $\theta$ 看成固定参数，而贝叶斯估计 p(theta|D) 是估计一个 $$\theta$$ 的分布，而不是一个值（点）！

高斯分布参数的贝叶斯估计：设参数 theta 的先验分布 p(theta)，数据 X = {x1, … , xn}，估计 p(theta|D)。这里假设单变量，只估计 p(theta|D) 的高斯分布的均值 mu，方差 sigma^2 已知：

1. 根据已知的先验高斯分布 P(theta) = N(mu0, sigma0^2)

2. 根据贝叶斯定理和独立性，可以得 p(theta|D) = 

<img src="https://s2.loli.net/2022/06/25/9nU37YI5kqDdj8A.png" alt="image-20220625191741658" style="zoom:50%;" />

估计均值 & 方差为：

<img src="https://s2.loli.net/2022/06/29/mwhWvl2gLouRy8a.png" alt="image-20220625192656515" style="zoom:50%;" />

共轭先验conjugate prior：若 p(x|theta) ，存在先验 p(theta)，使得 p(x|theta) 和 p(theta) 有相同的函数形式，从而简化推导和计算。如高斯分布的共轭先验分布仍然是高斯分布。

完成 inference 后，如何决策？输出一个分布，结果通常根据期望决定。

#### KDE（非参）

常用的参数形式基本都是单模的，不足以描述复杂的数据分布。因此应该直接以训练数据自身来估计分布。

例：直方图。每维 n 个bin，那么 n 维应该保存多少个bin的参数？$$n^d$$。太大了，且不光滑！

给定一组提取于未知分布 p(x) 的数据 $x_1,x_2,...,x_n$ ，任一点 x 处的核密度估计定义为：

$$
\hat{p}(x) = \frac{1}{nh} \sum^{n}_{i=1}K(\frac{x-x_i}{h})
$$

$$
K(x) \ge0, \int K(x)dx=1
$$

KDE 核函数与 SVM 的不同：在概率估计中被用于估计目标点周围的概率密度。而在SVM中，被用于计算两点间的核空间距离。

<img src="https://s2.loli.net/2022/06/25/OzKfk6DU5dah1Ng.png" alt="image-20220625193832796" style="zoom: 33%;" />

连续的。

窗宽确定：使得估计的积分均方误差 (mean integral square error,MISE) 达到最小，如下式

$$
MISE\{\hat{p}_h(x)\}=E[\int^{\inf}_{-\inf}\{\hat{p}_h(x)-p(x)\}dx]
$$


#### HMM（机器学习）

**隐马尔可夫性质**

$$P(X_t|X_{1:t-1})=P(X_t|X_{t-1})$$ ，无记忆性，当前状态的只跟上一个状态有关系。

**随机过程（stochastic process）**

$$\{X(t), t\in T\}$$ 是一系列随机变量的集合，用于描述一些过程的时间进化，目的是希望过去对现在有帮助。也就是说，对于每个 $$t \in T$$, $$X(t)$$ 是一个随机变量。索引 t 通常被解释为时间，因此把 $$X(t)$$ 作为 t 时流程的状态。

B：emission probability 发出观察值的概率。$$b_j(k)=Pr(O_t=V_k|Q_t=S_j)$$。当未知状态为 $$S_j$$ 时观察到为 $$V_k$$ 的概率。

**Problem 1. Evaluation**

概念：给定已知 $$\lambda = (A,B,\pi)$$ 的 HMM 模型，以及一个完整的输出序列 $$o=o_{1:T}$$，求该模型观察到该输出序列的概率 $$P(O|\lambda)$$。

作用：看出此模型对该观察序列的成绩，从而在多个模型中选择最适合的模型。

算法

1. Naive

假设隐状态序列 $q_{1:T}$ 已知：

$$
Pr(o_{1:T}|\lambda, q_{ 1:T}) = \prod^{T}_{t=1}Pr(o_t|q_t, \lambda) = \prod^{T}_{t=1}b_{q_i}(o_i)
$$

则必有

$$
Pr(o_{1:T}|\lambda) = Pr(o_{1:T}, q_{1:T}|\lambda) =\sum_{all\ Q}Pr(o_{1:T}|\lambda, q_{ 1:T})Pr(q_{1:T}|\lambda)
$$

时间复杂度 $$O(TN^T)$$

2. 对 Naive 的观察与优化——提取 $$b_i(o_i)$$

$$
Pr(o_{1:T}|\lambda)=\sum_{i=1}^{N}Pr(o_{1:T},Q_T=S_i|\lambda)\\
=\sum_{i=1}^{N}Pr(o_{1:T-1},Q_T=S_i|\lambda)Pr(O_T=V_k|Q_T=S_i,\lambda)\\
=\sum_{i=1}^{N}Pr(o_{1:T-1},Q_T=S_i|\lambda)b_i(o_T)
$$

3. 对 Naive 的观察与优化——提取 $$A_{ji}$$

$$
Pr(o_{1:T-1},Q_T=S_i|\lambda) = \sum_{j=1}^{N}Pr(o_{1:T-1},Q_{T-1}=S_j|\lambda)A_{ji}
$$

根据 2. 和 3. 的提取优化，可得

$$
Pr(o_{1:T}|\lambda)=\sum_{i=1}^{N}Pr(o_{1:T},Q_T=S_i|\lambda)\\
=\sum_{i=1}^{N}Pr(o_{1:T-1},Q_T=S_i|\lambda)b_i(o_T)\\
=\sum_{i=1}^{N}(b_i(o_T)\sum_{j=1}^{N}Pr(o_{1:T-1},Q_{T-1}=S_j|\lambda)A_{ji}) \\
$$

4. 前向算法 forward

定义 $$\alpha_{t}(i)=Pr(o_{1:t},Q_t=S_i|\lambda)$$。含义：对于已知参数 $$\lambda$$ 的模型，获得观测序列 $$o_{1:T}$$ 且 t 时刻隐状态为 $$S_i$$ 的概率。

初始化：$$\alpha_1(i)=Pr(o_{1},Q_1=S_i|\lambda) = Pr(Q_1=S_i|\lambda)Pr(o_{1}|Q_1=S_i,\lambda) = Pr(Q_1=S_i|\lambda)b_i(o_1)$$

前向递推：

$$
\alpha_{t+1}(i)=[\sum^{N}_{j=1} Pr(o_{1:t},Q_t=S_j|\lambda)A_{ji}]b_i(o_{t+1})\\
=[\sum^{N}_{j=1} a_{t}(j)A_{ji}]b_i(o_{t+1})
$$

结果：$$Pr(o_{1:T}|\lambda)=\sum^{N}_{i=1}Pr(o_{1:T},Q_T=S_i|\lambda)=\sum^{N}_{i=1} \alpha_T(i) $$

复杂度：$$O(TN^2)$$

⑤ 后向算法 backward

定义 $$\beta_t(i) = Pr(o_{t+1:T}|Q_t=S_i, \lambda)$$。含义：对于已知参数 $$\lambda$$ 的模型，已知 t 时刻状态为 $$S_i$$，未来观测到 $$o_{t+1:T}$$ 的概率。

初始化：$$\beta_T(i) = 1$$。

反向更新：

$$
\beta_t(i) = \sum^{N}_{j=1}A_{ij}b_j(o_{t+1})\beta_{t+1}(j)
$$

输出：$$Pr(o_{1:T}|\lambda)=\sum^{N}_{i=1}\pi_{i}b_i(o_{1})\beta_{1}(i)$$



**Problem 2：Decoding**

概念：给定已知 $$\lambda = (A,B,\pi)$$ 的 HMM 模型，以及一个完整的输出序列 $$o=o_{1:T}$$，求一个完全指定的隐变量序列 $$q_{1:T}$$ 的值。

作用：语音识别中状态可能有实际意义（各音节），可以用来观察模型结构，优化模型。

算法：

<img src="https://s2.loli.net/2022/06/29/LWcKyRP9Zk8xB4Y.png" alt="image-20220629185728038" style="zoom: 50%;" />

**Problem 3：Learning**

概念：发现 $$\lambda = (A,B,\pi)$$，使得对于固定的 N，T，和观察值 O，似然概率 $$P(O|\lambda)$$ 最大。

作用：最重要的问题

目前无法发现全局最优解，常用 Baum-Welch 算法。



### 5. 优化方法

>优化方法：极值条件，对偶，KKT，GD，SGD，EM，
>要知道凸优化和非凸优化，要知道凸优化的话，极值就是最优点，那么找最优点就是导数等于0
>要直到 SVM 里面的对偶问题，SVM 没有显式最优解，因此可以用 GD，Regression 有显式最优解
>在神经网络里面一般用 SGD，SGD 要有一个概念，为什么我们要用 SGD 和 GD？要知道二者区别，还得知道 SGD 优点
>要对概率模型的参数进行估计的话，可以考虑用 EM 进行参数估计，比如 HMM

凸优化定义：

$$
minimize \ f_0(x)  \\
subject \ to \ f_i(x)<=b_i,\ \ i=1,...,m
$$

其中，目标函数和约束函数都是凸函数，即

$$
f_i(\alpha x+\beta y) <= \alpha f_i(x) + \beta f_i(y) \\
\alpha + \beta = 1,\  \alpha >=0, \ \beta>=0
$$

#### [SVM 中的对偶 & KKT（机器学习）

#### GD & SGD

随机梯度下降每次只用一个样本，对于最优化凸问题，虽然不是每次迭代得到的损失函数都向着全局最优方向， 但是大的整体的方向是向全局最优解的，最终的结果往往是在全局最优解附近。但是相比于批量梯度，这样的方法更快，更快收敛。

批量梯度下降每次更新时用所有样本。对于最优化凸问题，可以达到一个全局最优。如果样本不多的情况下，当然是这样收敛的速度会更快。但是很多时候，样本很多，更新一次要很久。

#### EM & GMM（机器学习）

浙大



### 6. 距离度量

>（样本之间的）距离度量：l-p 范数, DTW, …
>要知道如何度量两个不同时间序列的样本之间的距离
>DTW 动态时间规整

$$l_0$$ 范数：向量 x 的非零元素的个数

<img src="https://s2.loli.net/2022/06/29/QEPADFUZL5hbsfv.png" alt="image-20220625200150788" style="zoom:50%;" />

DTW（Dynamic Time Warping）：动态时间规整

性质：1. 匹配是顺序的 2. 每个 $$x_i$$ 或 $$y_i$$ 都要有对应的匹配 3. 一个 $$x_i$$ 可以和多个 $$y_j$$ 匹配，反之亦然

<img src="https://s2.loli.net/2022/06/29/UdA6mkPbKY1phcR.png" alt="image-20220625202602917" style="zoom:50%;" />

递推公式：

<img src="https://s2.loli.net/2022/06/29/OeASiJYFf952cZh.png" alt="image-20220625202654161" style="zoom:50%;" />

#### 熵

单变量

$$
H=-\sum^{m}_{i=1}p_ilog_2p_i
$$

$$
h=-\int p(x)ln(p(x))dx
$$

双变量

$$
H(x,y)=-\sum_{x}\sum_{y}P(x,y)log_2P(x,y)
$$

$$
h=-\int p(x,y)ln(p(x,y))dxdy
$$

$$
H(X|Y) = \sum_{y}P(y)H(X|Y=y) = 
-\sum_{y}P(y)\sum_{x}P(X=x|Y=y)log_2P(X=x|Y=y) \\
= -\sum_{x,y}P(x,y)log_2 \frac{P(x,y)}{p(y)}
$$

$$
h(x,y) = -\int p(x,y)ln\frac{p(x,y)}{p(y)}dxdy
$$

熵之间的关系

H(X,Y)=H(X)+H(Y|X)=H(Y)+H(X|Y)

H(X|Y)<H(X)

H(Y|X)<H(Y)

互信息

$$
I(X;Y)=H(X)-H(X|Y) = \sum_{x,y}P(x,y)log_2 \frac{P(x,y)}{P(x)P(y)}
$$

KL 散度

$$
KL(P||Q)=\sum_{i} P_ilog_2\frac{P_i}{Q_i}
$$

$$KL(P||Q) \ge 0$$，等号成立条件：$$P_i=Q_i$$。不对称。

交叉熵

$$
CE(P,Q)=-\sum_{i}P_ilog_2Q_i \\
CE(P,Q)=H(p)+KL(P||Q)=-\sum_{i}P_ilog_2P_i+\sum_{i} P_ilog_2\frac{P_i}{Q_i}
$$



### 7. 损失函数

>损失函数：square, hinge, exponential, logistic, cross entropy, …
>线性回归：square
>SVM：hinge
>Adaboost：exp
>逻辑回归：logistic
>神经网络：cross entropy

#### Square（机器学习）

形式：

$$
L(f,y)=(f-y)^2
$$

线性回归中的 Square：

$$
L=\sum^{N}_{i=1}(y_i-\theta^Tx_i)
$$

#### Hinge

译为铰链损失。

形式：

$$
L(y,f(x)) = max(0,1-yf(x)),
$$

SVM 中的 Hinge：

$$
L = \frac{1}{2C}||w||^2+\sum^{N}_{i=1}max(0, 1-y_i(\theta^Tx_i+b))
$$

#### Exp

译为指数损失。

形式：

$$
L(y, f(x)) = exp[-yf(x)]
$$

Adaboost 中的 Exp：

$$
L(y, f(x)) = \frac{1}{n} \sum^{n}_{i=1} exp[-y_if(x_i)]
$$

#### Logistic（机器学习）

形式：

$$
L(y,f(x))=\sum_{l}y^l ln P(y^l=1|x^l,w)+(1-y^l)ln P(y^l=0|x^l,w) \\
=\sum_{l}y^l(w_0+\sum^{n}_{i=1}w_ix_i^l)-ln(1+exp(w_0+\sum^{n}_{i=1}w_ix_i^l))
$$

#### Cross entropy

形式：

$$
L(y,f(x)) = -\sum^{n}_{i=1}y_i logf(x_i)
$$



### 8. 评价准则

>评价准则：Acc, ROC, AP, Recall (TPR, true position rate), Precision, Bayes error, Bias-variance
>概念掌握
>Bayes error：取一个后验概率最大的去作为模型预测的输出
>Bias-variance：把模型的误差做一个偏执方差分解，需要直到模型的偏置和方差，以及是由什么决定的

PPT 3-4

