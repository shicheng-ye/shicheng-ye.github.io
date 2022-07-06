---
layout: post
title:  "[review]Machine learning courses"
date:   2022-07-06 15:09:45 +0800
categories: courses
---



#### 1. 线性回归 + 逻辑回归

> TIPS：什么是线性回归逻辑回归，损失函数有可能带正则项，为什么要加正则项因为要防止过拟合，损失函数要怎么定义，梯度下降好处有什么坏处有什么，最优参数表达式怎么写的

**损失函数**

**最优参数表达式**

损失函数带正则项的原因（补）：防止过拟合。[防止过拟合的另一种方法：k-fold交叉验证]

**定义（补）：**

回归模型

<img src="https://s2.loli.net/2022/06/16/7ptIHgE9TxmLqDY.png" alt="image-20220616211439417" style="zoom: 33%;" />

线性模型：

<img src="https://s2.loli.net/2022/06/16/iSARVj61pXs7uot.png" alt="image-20220616211840331" style="zoom:33%;" />

对于上式，假设b=0，则易得：

<img src="https://s2.loli.net/2022/06/16/38sicRAGgWkaBQ9.png" alt="image-20220616211950067" style="zoom: 33%;" />

矩阵形式可以写作为：

<img src="https://s2.loli.net/2022/06/16/CmTt9DBIVc564PX.png" alt="image-20220616212339948" style="zoom:33%;" />

显然，我们的目的就是求位置参数 theta，如何求解？构造最大似然估计（maximum likelihood estimator，MLE），找到 theta 使得似然概率最大。

最大似然估计的合理性在于这样一个假设：既然能出现这样一个数据分布，那么可以假设在当前的 theta 情况下，出现该数据分布的概率是很大的。因此可以进行最大似然估计。

最大似然的求解可以有两种：分析法，即令微分=0；迭代法，即（随机）梯度下降。

基于独立同分布的假设，n 个数据点的概率可以表示为：

<img src="https://s2.loli.net/2022/06/16/YGK2RtiLNy7ZVqW.png" alt="image-20220616212845691" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/25/SHtiPL5NZFBVDQJ.png" alt="image-20220616213531856" style="zoom:50%;" />

问：为什么这里的 p(x_i) 可以表示成1？

问题转化为：

<img src="https://s2.loli.net/2022/06/16/XCvn2zl1wBic5Iq.png" alt="image-20220616213559809" style="zoom:33%;" />

为简便计算，一般求对数 MLE：

<img src="https://s2.loli.net/2022/06/16/mEqR7yvndSDTxCU.png" alt="image-20220616213842804" style="zoom:33%;" />

第一项对于 theta 而言是常数项，省去，故最终优化目标为：

<img src="https://s2.loli.net/2022/06/16/ml7RKP58VQDMBTU.png" alt="image-20220616213936228" style="zoom:33%;" />

等价于：

<img src="https://s2.loli.net/2022/06/16/3ckBP5XQ2s8oZvI.png" alt="image-20220616223835964" style="zoom:33%;" />

**如何通过梯度下降求解参数：**

<img src="https://s2.loli.net/2022/06/16/kU1puR4iNY7TjKa.png" alt="image-20220616224131196" style="zoom:33%;" />

<img src="https://s2.loli.net/2022/06/16/k6xDJTvgwRCQU57.png" alt="image-20220616224144007" style="zoom:33%;" />

为保证对数似然是凸的，求二阶导（Hessian）矩阵：

<img src="https://s2.loli.net/2022/06/16/XkuaKYjnhz95xpR.png" alt="image-20220616224258646" style="zoom:33%;" />

如果 X 是满秩的，那么 XX 就是正定的，因此 theta_{MLE} = minimum。用正则化处理退化情况

令梯度为 0，解得：

<img src="https://s2.loli.net/2022/06/16/N6bi98ATIqmByjK.png" alt="image-20220616224419634" style="zoom:33%;" />

据此可以利用一些矩阵方式求解，方法有 Cholesky Factorization 等。

抑或是梯度下降求解 theta_{MLE}（rho 是学习率）：

<img src="https://s2.loli.net/2022/06/16/KgdqV8P1OoG6j4X.png" alt="image-20220616225107915" style="zoom:33%;" />

其中，对数似然求微分得到的系数 2 被并入 rho。

更好的办法——随机梯度下降：

<img src="https://s2.loli.net/2022/06/16/QxsKiuEzZS548WM.png" alt="image-20220616225520614" style="zoom:33%;" />

在非线性的情况，可以采用非线性变换，如 splines, radial basis functions 等。

##### 逻辑回归

<img src="https://s2.loli.net/2022/06/19/pZSXLig1uB8HQTe.png" alt="image-20220619150432337" style="zoom:33%;" />



<img src="https://s2.loli.net/2022/06/19/fUJOoXMxzVbYiGQ.png" alt="image-20220619150625491" style="zoom:33%;" />

要知道的就是 w，对于 w 的取值，我们可以令：

$$
\omega = argmax_{\omega} \prod_{l} P(y^l|x^l,w)
$$

其中，$$y^l$$ 和 $$x^l$$ 取之于训练集。上式写作 log-likelihood：

<img src="https://s2.loli.net/2022/06/19/fYuy1vN9mRKJl82.png" alt="image-20220619151102221" style="zoom:33%;" />

根据 y 只能取 0 或 1 的性质，把 argmax 右边的 sum 写作下式：

<img src="https://s2.loli.net/2022/06/19/yBqYNAuV8wDoXUc.png" alt="image-20220619151331602" style="zoom: 33%;" />

写出 loss 方程，直接开导！

<img src="https://s2.loli.net/2022/06/19/5XeWJgpL3DmnFUS.png" alt="image-20220619151806127" style="zoom:33%;" />

梯度下降：

<img src="https://s2.loli.net/2022/06/19/PXnCHxJT5Li9kFV.png" alt="image-20220619152345177" style="zoom:33%;" />

加入正则化，防止过拟合的版本：

<img src="https://s2.loli.net/2022/06/19/gMUjNX45zOZL2Af.png" alt="image-20220619152530114" style="zoom:33%;" />



#### 2. 过拟合

**什么是过拟合**

Low training error does not imply good expected performance

**降低过拟合的方法**

Reduce number of features + Keep all the features, but reduce values of parameters

① 损失函数加入正则项

② k-fold交叉验证



#### 3. 训练方法

>什么是过拟合、欠拟合，过拟合：训练集损失函数误差小，测试集大。怎么避免过拟合？加入正则项，使他训练集没那么好，增加模型的延展性；k-折交叉验证的k什么意思，分数据集怎么分，可以随机也可以不随机

一个衡量模型好坏的指标：

<img src="https://s2.loli.net/2022/06/19/FlpzMatZY5qsQbC.png" alt="image-20220619203215062" style="zoom: 50%;" />



**训练集-矫正集-测试集**

<img src="https://s2.loli.net/2022/06/19/2uViFwWhag4DAm7.png" alt="image-20220619204433308" style="zoom:33%;" />

使用验证集是为了快速调参，(网络层数，网络节点数，迭代次数，学习率）。另外用验证集还可以监控模型是否异常（过拟合），然后决定是不是要提前停止训练。

**留出法（Hold-out method）**

把数据集分此训练集(2/3)和测试集(1/3)，经常使用的情况：有几千个示例，每个类有几百个实例。

<img src="https://s2.loli.net/2022/06/19/e5OIa72Dv4HUfkE.png" alt="image-20220619203443206" style="zoom: 50%;" />



更大的测试集可以得到更精确的错误率估计。

有时有些类的实例很少，此时就要用 Stratified (分层) sample，确保每个类在训练测试集中的比例大致相等，这可以减少模型方差。



**Repeated hold-out method** 

在每次迭代中，随机选择一定比例数据进行训练（可能分层）。对不同迭代的错误率进行平均，以得出总体错误率。

仍不是最佳：不同的测试集重叠，但我们希望每个数据都被至少测试一次。



**k-fold cross validation**

① 数据分成 k 等分个子集。② 每次选 k 份中未选择过的一份当测试集，其他训练集。

每个子集在交叉验证就分层过了。总 estimate 就是各次 estimate 的平均。



**k-fold cross validation with validation and test sets**

这是个稍微不那么精细的方法

① 数据分成 k 等分个子集。② 每次选 k 份中未选择过的一份当测试集，剩余的选个当验证集，其他就是训练集。

最优的 k：10，实验证明可以得到最精确的 estimate。



**Bootstrap method**

<img src="https://s2.loli.net/2022/06/25/oTNsXG7bHMu6UY3.png" alt="image-20220620102258752" style="zoom: 50%;" />

我们随机地从数据集中抽取出 n 个数据组成一个新的数据集（允许重复）。

<img src="https://s2.loli.net/2022/06/20/v9ZPYdwJLx37Bib.png" alt="image-20220620102505143" style="zoom: 50%;" />

由于只在 63% 的数据集上训练，因此测试集上的 error estimate 不太好，故联合训练集上的 error：

<img src="https://s2.loli.net/2022/06/25/VroIE9T8L3dwCPu.png" alt="image-20220620103213161" style="zoom: 50%;" />

重复以上过程多次，平均结果。

总结：

hold-out method：large data

cross-validation method： middle-sized data

leave-one-out and bootstrap method：small data



#### 4. 决策树

![image-20220620103458461](https://s2.loli.net/2022/06/25/8XbqAC2ezLvjJYV.png)

>决策树做分类的监督学习算法，熵的定义

**熵的求解**

<img src="https://s2.loli.net/2022/06/20/9C2TJaINsQSevrw.png" alt="image-20220620104114188" style="zoom: 50%;" />

$$log(p_i)$$ 定义为信息量。

##### 条件熵的求解

![img](https://pic1.zhimg.com/80/v2-f925bd0dba2f4584ebd78efea6c9864c_720w.png)

<img src="https://s2.loli.net/2022/06/20/NkF7ymxfM2tQYpI.png" alt="image-20220620111606275" style="zoom:50%;" />

**求解对应属性的信息增益**

<img src="https://s2.loli.net/2022/06/20/LeoA34iYJxOC9Rr.png" alt="image-20220620111639812" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/20/KrRZDhVyWu39jfz.png" alt="image-20220620111705567" style="zoom:50%;" />



**决策树的构建**

预剪枝，后剪枝

<img src="https://s2.loli.net/2022/06/20/pLagxXGmhu2FeqU.png" alt="image-20220620111819108" style="zoom: 67%;" />



#### 5. SVM

![image-20220620111901955](https://s2.loli.net/2022/06/20/92VxBYKZTsEnmQo.png)

>标准的SVM是个线性的分类器，基本思想：找出一个分界面，让分界面离正负样本的距离最大，不需要背答对了大概意思就行，损失函数怎么定义，不需要会求解，为什么引入核函数，有什么功能

**SVM 的基本思想**

找出一个分界面，让分界面（margin）离正负样本（support vector）的距离最大

点到直线的距离：

<img src="https://s2.loli.net/2022/06/20/wSNbjhR3mc1EprZ.png" alt="image-20220620112504919" style="zoom:50%;" />



**SVM 的损失函数**

Hinge 损失函数

$$
L(y, f(x)) = [1-yf(x)]_+ \\
z_+=
\begin{cases}
z,z \ge 0 \\
0,z \le 0
\end{cases}
$$

<img src="https://www.freesion.com/images/712/08b2261140aa01b193bf2546c55926a0.png" alt="在这里插入图片描述" style="zoom: 67%;" />

SVM 的优化目标

$$
最小化：\frac{1}{2}||w||^2 + C\sum^{N}_{i=1}\delta_i\ \\
限制条件： (1)\ \delta_i>=0,(i=1-N)\\
(2)\ y_i(w^TX_i+b) >= 1-\delta_i,(i=1-N)
$$


SVM 的损失函数

$$
\frac{1}{2}||w||^2+C\sum^{N}_{i=1}max(0, 1-y_i(wx_i+b))
$$

提出公因子 C，等价于

$$
\frac{1}{2C}||w||^2+\sum^{N}_{i=1}max(0, 1-y_i(wx_i+b))
$$

参考：https://blog.csdn.net/guofei_fly/article/details/102750900

**SVM 中的核函数**

<img src="https://s2.loli.net/2022/06/25/6LHme9akUO2ixu1.png" alt="image-20220620113232679" style="zoom:50%;" />

高维非线性计算资源消耗大，故映射到线性低维。

根据对 SVM 优化问题的观察，可以得知数据点只以点积的形式出现：

<img src="https://s2.loli.net/2022/06/20/BCe9FviQfEswd61.png" alt="image-20220620113548007" style="zoom:50%;" />

因此，无需考虑具体的映射 phi 函数的形式，只需要考虑核函数：

<img src="https://s2.loli.net/2022/06/20/ztsNlJa7D8wkEyi.png" alt="image-20220620113646068" style="zoom:50%;" />

举例而言：

<img src="https://s2.loli.net/2022/06/25/lsecmURo8HkL6Vi.png" alt="image-20220620113739303" style="zoom:50%;" />

要求核函数满足 Mercer function，即要求正定（对于nxn的矩阵，entry[i,j]=K(xi,xj)）。

基本的核函数：

<img src="https://s2.loli.net/2022/06/20/CyiWNYSKzEPBArJ.png" alt="image-20220620114131555" style="zoom:50%;" />



#### 6. PCA

![image-20220620114523211](https://s2.loli.net/2022/06/20/bIlwEBOWS9N2Hzu.png)

>PCA基本思想：降维，把最关键的维度找出来。PCA无监督的。
>
>PCA三种理解的角度：通过重构误差最小推出PCA的定义公式；通过方差最大的思想推出PCA；通过奇异值分解的方法推出PCA。
>
>PCA有进行一些假设约束，如两两方向之间正交。推导过程要知道，比如PCA重构误差的推导。PCA有什么缺点：要求方向正交，而这不一定是合理的。

**PCA 的基本思想**

降维，把最关键的维度找出来，以代表大部分的信息。



**PCA 的三种理解角度**：最小重构误差

正交的概念：

<img src="https://s2.loli.net/2022/06/25/q67d8aQrOHNEWu4.png" alt="image-20220620164104895" style="zoom:50%;" />

正交定理（举个例子就能理解，$$\alpha_{i}$$ 类似投影长度）：

<img src="https://s2.loli.net/2022/06/20/JY8tlMweoGU1CAW.png" alt="image-20220620164120492" style="zoom: 50%;" />

<img src="https://s2.loli.net/2022/06/20/f3mq5YuFBtTV6SA.png" alt="image-20220620164410215" style="zoom:50%;" />

当前的目标，就是找到这几个正交向量，以最好  地表示原数据。

PCA(主成分分析)所对应的数学理论是 SVD。而奇异值分解本身是完全不需要对矩阵中的元素做标准化或者去中心化的。但是对于机器学习，我们通常会对矩阵（也就是数据）的每一列先进行标准化。

<img src="https://s2.loli.net/2022/06/20/Dq8LxuJfKAXYrNb.png" alt="image-20220620200743365" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/20/WZyETCcNzKkUD54.png" alt="image-20220620200758681" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/20/q83lrapPHICT5Vx.png" alt="image-20220620200813328" style="zoom:50%;" />

Frobenius norm

$$
||X||_{F} = \sqrt{\sum_{i} \sum_j X_{i,j}^2}
$$

<img src="https://s2.loli.net/2022/06/20/SBcbvxlTGajD281.png" alt="image-20220620200824009" style="zoom:50%;" />



<img src="https://s2.loli.net/2022/06/20/IwqFd2GLfZNYUEo.png" alt="image-20220620200848625" style="zoom:50%;" />



<img src="https://s2.loli.net/2022/06/20/EAeJ5HyxTLpagX8.png" alt="image-20220620201027218" style="zoom:50%;" />



**PCA 的三种理解角度**：最大化方差



![img](https://pic3.zhimg.com/80/v2-0c361ad3dbb56d96e0ed85fbb6701a06_720w.jpg)

最大化方差等价于尽可能多地保留原始数据的信息。

以其中一个投影坐标方向 $$u_1$$ 为例，求其方差表达式：

<img src="https://s2.loli.net/2022/06/20/EiQzg76lsfRMBah.png" alt="image-20220620201121960" style="zoom: 50%;" />

类似前文所述，要使的 var 最大，等价于让 $$u_1$$ 是 S 的那个最大特征值的特征向量。



**PCA 的三种理解角度**：SVD 分解

<img src="https://s2.loli.net/2022/06/20/q9BjcKtP6ICi5rp.png" alt="image-20220620201616504" style="zoom: 50%;" />

<img src="https://s2.loli.net/2022/06/25/my1vuTYa5Wz8JGp.png" alt="image-20220620201650161" style="zoom:50%;" />



#### 7.  聚类

![image-20220620201752216](https://s2.loli.net/2022/06/25/UYWsd43SkaAEblO.png)

>k是什么？k个聚类。初始选取的k个点可以是随机的也可以是自己定义的。kmeans为什么可以收敛？可以通过实验的方法来了解k的选取。不同的初始状态会导致不同的结果。

**K-Means 聚类的思想**

在数据集中根据一定策略选择K个点作为每个簇的初始中心，然后将数据划分到距离这K个点最近的簇中，但形成的新簇并不一定是最好的划分，因此生成的新簇中，重新计算每个簇的中心点，然后在重新进行划分，直到每次划分的结果保持不变。

**K-Means 聚类的步骤**

① Ask user how many clusters they’d like.

② Randomly guess k cluster Center locations

③ Each datapoint finds out which Center it’s closest to.

④ Each Center finds the centroid of the points it owns

⑤ Jumps to ③，Repeat until terminated!

**K-Means 聚类的目标函数**

<img src="https://s2.loli.net/2022/06/21/1jMsx9iXITu3gLA.png" alt="image-20220621195837743" style="zoom:50%;" />

$$Encode(x_i)$$ 可以理解为把数据点 $$x_i$$ 归到第几个聚类，$$Decode[j]$$ 可以理解为把第 j 个聚类的中心 $$c_j$$。

要最小化 Distortion。① 这就要求 $$x_i$$ 必须被归到离他最近的聚类。② 同时，还要求对 $$c_j$$ 对 Distortion 的偏微分都为 0：

<img src="https://s2.loli.net/2022/06/21/SM9Nbs16FlmLtHB.png" alt="image-20220621200517118" style="zoom:50%;" />

满足 minimum 的情况，也就是满足 $$c_j$$ 是该聚类中的点的均值的情况。

① 和 ② 连续操作没意义，但是交替操作就很有意义，这即是 K-means。为什么可以收敛呢？

有限个点分到有限个聚类里，这样配置/聚类的可能情况是有限的。同时，当配置改变，意味着得到了更好的 Distortion。每次改变都是更好的配置，如果一直改变，迟早会用光所有的配置。

不一定能全局最优。因此，谨记：选好初始值，或者跑多次不一样的k-means。

对选好初始值的一种可行方案：首先随便选个数据点做聚类中心，之后选的聚类中心尽可能选离所有已选聚类中心远的数据点。



**K-Means 聚类的 K 的选取**

常规方法：最小化 Schwarz Criterion (also related to the BIC, schwarz's bayesian criterion (bic))

<img src="https://s2.loli.net/2022/06/21/Nr6iYRcZe8BKOnh.png" alt="image-20220621201736841" style="zoom: 50%;" />





#### 8. EM 算法

背景——欲解决的问题

<img src="https://s2.loli.net/2022/06/21/8smHPfpizQuCMGd.png" alt="image-20220621202550971" style="zoom:50%;" />

**E 步** + **M 步**

<img src="https://s2.loli.net/2022/06/21/fItr2GPplesRZyV.png" alt="image-20220621211812481" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/21/E6PnbiGUND3I8aS.png" alt="image-20220621211829792" style="zoom:50%;" />

理论推导：

先重新表达所要优化的对数似然函数：

<img src="https://s2.loli.net/2022/06/25/J47MrBzUauFkNV8.png" alt="image-20220621203424720" style="zoom:50%;" />



<img src="https://s2.loli.net/2022/06/21/pFKkdUzD7rxcEGS.png" alt="image-20220621212332088" style="zoom:50%;" />



<img src="https://s2.loli.net/2022/06/21/XLMBO2mAv9Z6jtY.png" alt="image-20220621212346646" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/25/RHqwNm8ICAYnyc1.png" alt="image-20220621212358971" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/21/KSPc1XvpboqmU9e.png" alt="image-20220621212426612" style="zoom:50%;" />

强烈建议结合浙大的课程一起复习！

**EM 算法一般形式**

① 随机选取 $$\theta_0$$

② E-step

$$
Q_i(z_i) = P(z_i|x_i, \theta_k) = \frac{P(z_i,x_i|\theta_k)}{P(x_i|\theta_k)}=\frac{P(z_i,x_i|\theta_k)}{\sum_{z_i} P(z_i, x_i|\theta_k)}
$$

③ M-step

$$
\theta_{k+1}=argmax_{\theta} \sum_{i=1}^{N} \sum_{z_i}Q_i(z_i) log\frac{P(z_i,x_i|\theta_k)}{Q_i(z_i)}
$$

④ 回到 ②，直至收敛。



**高斯混合聚类算法的思想和步骤**

一种 soft(fuzzy) 的聚类

实现思想：根据 EM 算法，针对每个数据点，为之分配属于每个聚类的概率

高斯分布

<img src="https://s2.loli.net/2022/06/22/CqPZydVhtUkpaj6.png" alt="image-20220622150629542" style="zoom:50%;" />

高斯分布的均值与方差：

<img src="https://s2.loli.net/2022/06/22/q1pVILjWGrEba4h.png" alt="image-20220622150851026" style="zoom:50%;" />

开始极大似然估计：

<img src="https://s2.loli.net/2022/06/22/1RAtDoiS8hKf3F6.png" alt="image-20220622150709006" style="zoom:50%;" />

转为对数似然估计：

<img src="https://s2.loli.net/2022/06/22/Ox84ADUYJquFtQs.png" alt="image-20220622150728816" style="zoom:50%;" />

E 步 —— 求出数据点属于每个聚类的比重：

<img src="https://s2.loli.net/2022/06/22/hIHJOAWxZKsqv6C.png" alt="image-20220622151427673" style="zoom:50%;" />

M 步 —— 更新高斯分布的参数：

<img src="https://s2.loli.net/2022/06/25/YGpvCBXmrwZWxAJ.png" alt="image-20220622151501063" style="zoom:50%;" />

https://zhuanlan.zhihu.com/p/85338773

#### 9. 推荐系统

![image-20220622160643079](https://s2.loli.net/2022/06/22/a2qrV1MUFRLeo5v.png)

>打分矩阵L分解成用户矩阵U和item矩阵I，然后可以用梯度下降求，目标函数怎么定义？U*I的结果尽可能接近L。
>基于用户：得到打分矩阵，计算相似度量公式，计算两两相似度，找出k个最像的用户，计算打分。
>基于商品：有时候用户很多，但商品数量有限。得到打分矩阵，确定一个商品之间相似度的度量公式。
>基于内容：考察商品之间的相似度，不仅考虑打分，还考虑商品的描述内容。
>冷启动：概念，新用户进来很难对其进行推荐，新商品进来不知道跟哪些商品相似，难以推荐新商品。
>数据稀疏的问题：打分矩阵的数据是很稀疏的。

https://zhuanlan.zhihu.com/p/28577447

[SVD 分解](https://blog.csdn.net/qq_58535145/article/details/122651843)



**基于矩阵分解的推荐系统** 

打分矩阵 L 分解成用户矩阵 U 和商品矩阵 I，然后可以用梯度下降求，目标函数怎么定义？U * I 的结果尽可能接近 L。

<img src="https://s2.loli.net/2022/06/29/1eIBCKohqjzwUGQ.png" alt="image-20220629102319437" style="zoom:50%;" />



**基于用户的协同推荐**

![image-20220629094502874](https://s2.loli.net/2022/06/29/15cNKrYSz67Tte8.png)

根据打分矩阵，计算相似度量公式

<img src="https://s2.loli.net/2022/06/22/UImglxuAvd8YGoq.png" alt="image-20220622182448962" style="zoom:50%;" />

观察 sim(a, b)，其实就是相关系数（Pearson correlation）的计算。

<img src="https://s2.loli.net/2022/06/25/m9vDk6iMAcpF8OQ.png" alt="image-20220622185202056" style="zoom:50%;" />

问题：可能会导致只给出一些特定的 items。

解决：对差异较大的项目给予更多权重；significance weighting；Case amplification。

总结：memory-based，不适用现实场景，现实中这个矩阵太大。

**基于商品的协同推荐**

![image-20220629094512656](https://s2.loli.net/2022/06/29/G6u4xBhybcMfo9r.png)

<img src="https://s2.loli.net/2022/06/25/IA8ZXt6OnjYUkhq.png" alt="image-20220622185916132" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/25/Ayaqb8OCjeBhSxn.png" alt="image-20220622191033984" style="zoom:50%;" />



**基于内容的协同推荐**

基本思想：根据推荐物品或内容的元数据，发现物品或者内容的相关性，然后基于用户以往的喜好记录，推荐给用户相似的物品。即考察商品之间的相似度，不仅考虑打分，还考虑商品的描述内容。

应用：电影 A 和 C 的类型都是爱情和浪漫，那么就会给看过电影 A 的人推荐电影 C。



**冷启动问题**

<img src="https://s2.loli.net/2022/06/25/3r2tRfuQJYW1967.png" alt="image-20220622190514423" style="zoom:50%;" />



**数据稀疏的问题**

<img src="https://s2.loli.net/2022/06/25/unjKe5YSromxyRG.png" alt="image-20220622190602455" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/06/25/8TADf4nGsN1Vemo.png" alt="image-20220622190618711" style="zoom:50%;" />