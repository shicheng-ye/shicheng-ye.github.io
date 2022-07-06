概率分类法

基本问题：① 假设有两个类，omega_1 和 omega_2，② 假设某向量样本 X，要么有 X in omega_1，要么有 X in omega_2。

求 P(omega_1 |X) 与 P(omega_2 |X)，P(omega_1 |X) + P(omega_2 |X) = 1。

分类问题：P(omega_1 |X) > P(omega_2 |X) ，则 X in omega_1。

 

根据贝叶斯公式，

P(omega_1 |X) = P（X, omega_1) / P(X) = P（X|omega_1) P(omega_1)/ P(X) 

P(omega_2 |X) = P（X, omega_2) / P(X) = P（X|omega_2) P(omega_2)/ P(X) 

要比较P(omega_1 |X) > P(omega_2 |X)，只需要比较上式的分子。

其中，P(omega_1) 和 P(omega_2) 叫做 omega 的先验概率。P（X|omega_1) 和 P（X|omega_2) 叫做 X 在 omega 上的条件概率，P(omega_1 |X) 和 P(omega_2 |X) 叫做 X 在 W 上的后验概率。

人工神经网络输出分类概率，基本上是在模拟 P(omega_1 |X) 和 P(omega_2 |X)。即便如此，我们仍必须要非常关注先验概率。假设训练二分类模型，训练的时候两类五五开，但是测试的时候九一开，就会出现很大的问题。也即是我们要在测试和训练的时候保证两个先验概率是差不多的。实操时总是有一个把样本集打乱的步骤，其原因也便是在这里。



接下来讲重点。举一个二分类的例子，若不知道先验概率，则**假设所有先验概率一样**。在此情况下，分类准则

若 P（X|omega_1) < P（X|omega_2) 则 X in omega_2，反之 X in omega_1

如何估计  P（X|omega) ，或者说给定一组 X_i in omega，如何求 P（X|omega) 。这个问题叫做概率密度估计问题。