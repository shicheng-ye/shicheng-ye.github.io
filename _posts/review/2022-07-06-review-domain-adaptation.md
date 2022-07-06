---
layout: post
title:  "[review]Domain adaptation"
date:   2022-07-06 11:09:45 +0800
categories: courses
---



# 27 Domain Adaptation

训练资料跟测试资料的分布是不一样的，叫做 ==Domain Shift==。

解决办法是 ==Domain Adaptation==，它也可以看做是 ==Transfer Learning== 的一种。

Transfer Learning ：在 A 任务上学到的技能可以被用在 B 任务上

Domain Adaptation：你的训练资料是一个 Domain，你的测试资料是另外一个 Domain，你在训练资料上面学到的资讯可以要把它用到另外一个 Domain 上。

## Domain Shift

两者可能情况。一，输入资料即训练集和测试集的分布不同。二，输入跟输出虽然分布相同的，但它们之间的关係变了，比如训练集叫做 0 的东西在测试集里叫做 1。

今天只考虑前者。记测试集为 ==Target Domain==，训练集为 ==Source Domain==。

## Domain Adaptation  

分三种情况考虑：

其一，在 Target Domain 上有一大堆的资料且配有 Label，那就直接拿 Target Domain 的资料来训练。

其二，在 Target Domain 上有一点点的资料且配有 Label，那就拿他们来微调，即不要在 Target Domain 上的资料上跑太多的 Iteration。

其三，在 Target Domain 上有一大堆的资料但没有 Label。找个 Feature Extractor，它会把 Source 和 Target 不一样的部分拿掉，只抽取出它们共同的部分。

其四，在 Target Domain 上有一点点的资料且没有 Label。有一个方法叫做 ==Testing Time Training==,它的缩写是 TTT。

<img src="https://s2.loli.net/2022/07/02/YkL3rCt54DKV1hd.png" alt="image-20220702171146183" style="zoom:50%;" />



### Domain Adversarial Training

怎麼找出这样的一个 Feature Extractor 呢？那其实我们可以把一个一般的 Classifier 分成 Feature Extractor 跟 Label Predictor 。

<img src="https://s2.loli.net/2022/07/02/KRqyn5MD2SxmYE3.png" alt="image-20220702172724450" style="zoom:50%;" />

Domain Adaptation 的一种方法 ==Domain Adversarial Training==

训练 Feature Extractor：让 Source Domain 的图片得到的 Feature，跟 Target Domain 的分不出差异。

训练 Domain Classifier：二元分类器，区分这个 feature 是来自於 Source Domain,还是来自於 Target Domain。

Domain Adversarial Training 很像是 GAN。可以把 Feature Extractor 想成是 Generator，把 Domain Classifier 想成是 Discriminator。

Generator 好像优势太大了，它只要都输出 0 不就无法区分了吗？不行，都输出 0 虽然 Domain Classifier 无法区分，但 Label Predictor 也无法区分！

接下来考虑参数优化。Label Predictor 要做的事情就是让这个 Source Domain 的 Image 分类越正确越好，即最小化 Loss（交叉熵，分类问题有交叉熵）。Domain Classifier 要做的事情就是让 Domain 的分类越正确越好，也是最小化交叉熵。

Feature Extractor 要做的事情是，它又要保证能让 Label Predictor 有个好结果，又要骗过 Domain Classifier，故把 loss 设为 $L-L_d$。



#### Limitation 

刚才这整套想法有一个小小的问题

<img src="https://s2.loli.net/2022/07/02/Hrnl2S15keas3fT.png" alt="image-20220702173655699" style="zoom:50%;" />

直觉上讲右边更好，所以我们是不是应该要让右边的状况发生呢？怎么做呢？也许一个可能的想法：我们既然知道分界点在哪裡，那我们应该要让这些方形远离这一个分界点。



#### Considering Decision Boundary  

什麼叫做离 Boundary 越远越好呢？如果今天输出的结果非常地集中，即 Entropy 小，叫做离 Boundary 远。反之则近。

到目前為止都假设说，Source Domain 跟 Target Domain，它的类别都要是一模一样。但是真的一定会这样吗？

<img src="https://s2.loli.net/2022/07/02/wjvbz6ytZYGfS7H.png" alt="image-20220702174451574" style="zoom:50%;" />



实线的圈圈代表，Source Domain 裡面有的东西，这个虚实线的圈圈代表 Target Domain 裡面有的东西。所以在这个前提之下，你说你要让 Source Domain 的 Data 跟 Target Domain 的 Data，它们的 Feature 完全 Match 在一起，那意味著说，你硬是要让老虎去变得跟狗像，到时候你就分不出老虎这个类别了。



## Domain Generalization

但其实还有一个更严峻的状况，如果我们对 Target Domain 一无所知的话怎麼办呢？这种情况通常就叫 ==Domain Generalization==。

我们期待机器在 Testing 的时候，不管来什麼样的 Domain，它都可以处理。

Domain Generalization 又分成两种状况：其一，训练资料本来就包含了各式各样不同的 Domain 的数据；其二，训练资料只有一个 Domain，做 Data Augmentation。

