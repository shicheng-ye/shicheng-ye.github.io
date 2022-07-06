---
layout: post
title:  "[review]Generative adversarial network"
date:   2022-07-06 11:09:45 +0800
categories: courses
---



# GAN_P1

# Generation

## Network as Generator

输入 x 和从一个distribution 裡面 sample 出来的 z，输出变成了一个复杂的 distribution。这种输出 distribution 的 network 称之为==generator==。

<img src="https://s2.loli.net/2022/07/02/eDOx7rbhcL9BEZA.png" alt="image-20220702205648601" style="zoom:50%;" />

## Why distribution

为什么要输出一个分布？有时候需要这样。

例子：video prediction，即给机器一段的影片，然后它要预测接下来会发生什麼事情。训练资料裡面同样的输入，有时候同样的转角有两种可能性。所以你的 network 学到的就是两面讨好。

什麼时候我们会特别需要这？我们的任务需要一点创造力的时候。通俗讲，们想要找一个function，但是同样的输入有多种可能的输出，他们都是对的。



# Generative Adversarial Network (GAN)

generative 的 model，其中一个非常知名的就是==generative adversarial network==。

## Anime Face Generation

例子：让机器生成动画人物的,二次元人物的脸。

<img src="https://s2.loli.net/2022/07/02/jlqBn7UevwaStmH.png" alt="image-20220702210030736" style="zoom: 50%;" />



## Discriminator

在GAN裡面除了==generator==以外还有一个 ==discriminator==。

discriminaton 也是个 network，它的作用是：拿一张图片作為输入，它的输出是一个数值。越大代表越像是真实的二次元图像。 

## Basic Idea of GAN

物竞天择。对应到 GAN，枯叶蝶就是 generator，那它的天敌就是 discriminator。

generator 生成二次元图像。discriminator 分辨二次元图像。

## Algorithm

#### Step 0：初始化 generator 和 discriminator 的参数。

#### Step 1: Fix generator G, and update discriminator D

从这个 gaussian distribution 裡面去 sample 一堆 vector，把这些 vector 丢到 generator 裡面，它就吐出一些图片。

你会有一个 database，这个database裡面，有很多二次元人物的头像。

接下来就拿真正的二次元人物头像，跟 generator 產生出来的结果，去训练你的discriminator。discriminator 它训练的目标是要分辨，真正的二次元人物跟 generator 產生出来的二次元人物。

这对於 discriminator 来说是一个分类的问题。也可以说是 regression 的问题。

<img src="https://s2.loli.net/2022/07/02/yVjMHO91l8wvBYd.png" alt="image-20220702211803640" style="zoom:50%;" />

#### Step 2: Fix discriminator D, and update generator G

我们把 generator 生成的图片丢到 Discriminator 裡面，Discriminator 会给这个图片一个分数，那 generator 是要 Discriminator 的输出值越大越好

举例来说 generator 如果是五层的 network，Discriminator 如果是五层的 network，把它们接起来我们就把它当作是一个十层的 network 来看待。这个十层的network裡面，其中某一隐藏层的输出就是代表一张图片。

我们要做的事情是,整个巨大的 network 啊,它会吃一个向量作為输入，然后他会输出一个分数,那我们希望调整这个 network，让输出的分数越大越好。==gradient ascent== 来优化。

<img src="https://s2.loli.net/2022/07/02/pohEWjL1BzN692T.png" alt="image-20220702211815139" style="zoom:50%;" />





# GAN_P2_Theory behind GAN

接下来讨论為什麼这个 Generator 跟 Discriminator 的互动，可以让我们的 Generator產生像是真正的人脸的图片。

那我们先来弄清楚训练的目标到底是什麼，我们想要 Minimize 的是让 Generator 产生的 Distribution 和 真正 Data 的 Distribution 越接近越好。

<img src="https://s2.loli.net/2022/07/02/SrRm7qka3Gznywl.png" alt="image-20220702212331965" style="zoom:50%;" />

Div = Divergence。红色下划线的函数也就表示了我们的 Loss Function。

常见的 Divergence 计算方法：

<img src="https://s2.loli.net/2022/07/02/NcdJfC34mDreIQa.png" alt="image-20220702212648534" style="zoom:50%;" />

<img src="C:%5CUsers%5Cysc%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5Cimage-20220702212653606.png" alt="image-20220702212653606" style="zoom:50%;" />



但是我们这边遇到一个困难的问题，这个 Divergence 很难算的。而==GAN==是一个很神奇的做法,它==可以突破,我们不知道怎麼计算 Divergence 的限制==。

我们不需要知道 PG 跟 Pdata 它们实际上的 Formulation （对应公式的 P(x) 和 Q(x)）长什麼样子，只要能从 PG 和 Pdata这两个 Distributions Sample 东西出来，就有办法算 Divergence。

## Discriminator

如何在只有做 Sample 的前提之下估测出 Divergence？那这个就是要靠 ==Discriminator== 的力量。

Discriminator 优化的过程，你也可以把它写成式子：

<img src="https://s2.loli.net/2022/07/02/r865BCpik9Ihtlc.png" alt="image-20220702213617546" style="zoom:50%;" />

这个 Discriminator 可以去 Maximize某一个 Function,我们这边叫做 ==Objective Function==（我们要 Maximize 的东西,我们会叫 Objective Function,如果 Minimize 我们就叫它 Loss Function）。

- $E_{y\sim P_{data}}[logD(y)]$ 我们有一堆 Y,它是从 Pdata 裡面 Sample 出来的,也就是它们是真正的 Image,而我们把这个真正的 Image 丢到 D 裡面,得到一个分数再取$logD(y)$

- $E_{y\sim P_G}[log(1-D(y))]$ 那另外一方面,我们有一堆 Y,它是从 PG 从 Generato r 所產生出来的,把这些图片也丢到 Discriminator 裡面,得到一个分数,再取 $log(1 - D (y))$


那这边最神奇的地方是这一个式子，这个红框框裡面的数值,它跟 JS Divergence 有关。假设 PG 跟 Pdata 的 Divergence 很小，所以这个 Objective 这个 V 的 Maximum 的值就比较小。所以小的 Divergence，对应到小的这个 Objective Function 的Maximum 的值。

<img src="C:%5CUsers%5Cysc%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5Cimage-20220702214350465.png" alt="image-20220702214350465" style="zoom:50%;" />



## Tips for GAN

技巧之一： ==WGAN==。

在此之前先讲 JS Divergence 有什麼样的问题。

### JS divergence is not suitable

PG 跟 Pdata 有一个非常关键的特性是：它们重叠的部分往往非常少。

原因有二：其一，那图片其实是高维空间裡面的一个低维的 Manifold，二次元人物的头像它的分布在高维的空间中其实是非常狭窄的。其二，我们对 PG 跟 Pdata,它的分布的理解来自於 Sample，如果采样不全有重叠也发现不了。

JS Divergence 有个特性，是两个没有重叠的分布，JS Divergence 算出来,就永远都是 Log2。因此用 JS Divergence 的时候，你就假设你今天在 Train 一个 Binary 的 Classifier，你会发现实际上你通常 Train 完以后正确率几乎都是 100%。

因為你 Sample 的图片根本就没几张，它直接用硬背来分辨。所以这时候 accuracy 没啥用。

### Wasserstein Distance

假想你在开一台推土机,那你把分布 P 想成是一堆土，把分布 Q 想成是你要把土堆放的目的地，那这个推土机把 P 这边的土，挪到 Q 所移动的平均距离就是 Wasserstein Distance。

<img src="https://s2.loli.net/2022/07/02/YbfdnjBgKyG7MiQ.png" alt="image-20220702215728448" style="zoom:50%;" />



但是推土的办法有很多种。因此光只是要计算一个 Distance，居然还要解一个 Optimization 的问题，解出这个 Optimization 的问题，才能算 Wasserstein Distance。先讲 Wasserstein Distance 能给我们什么好处。

<img src="https://s2.loli.net/2022/07/02/L2exJ7objlQV6RU.png" alt="image-20220702215942823" style="zoom:50%;" />



由左向右的时候，Wasserstein Distance 是越来越小的，表明 Generator 在进步。JS Divergence 却不变。

### WGAN

用 Wasserstein Distance 来取代 JS Divergence 的时候，这个 GAN 就叫做 WGAN。

接下来你会遇到的问题就是，Wasserstein Distance 是要怎麼算。

解下面这个 Opimilazion 的 Problem，解出来以后你得到的值就是 Wasserstein Distance。

<img src="https://s2.loli.net/2022/07/02/BQdKpZU4hnojlkT.png" alt="image-20220702220447872" style="zoom:50%;" />

即我们想要 Discriminator 对 Pdata 输出越大越好，对 PG 的 输出越小越好。 

限制：D 必须要是一个 1-Lipschitz 的 Function。

1-Lipschitz 不知道是什麼的话也没关係。可以想象成 D 必须要是一个足够平滑的 Function。



<img src="https://s2.loli.net/2022/07/02/zW8YZsXSBRuwAIn.png" alt="image-20220702220721319" style="zoom:50%;" />

否则，就会出现无限大的情况。这会导致要优化的目标越来越大，这下就又不能收敛力（悲。

接下来的问题就是怎麼做到 1-Lipschitz 的这个限制。

想法一：只需 Train Network 的时候，让 Training 的那个参数，要求它放得在 C 跟 -C 之间，如果参数更新后超过就设为 C 就设为 C，小于 -C 就设为 -C。但这样其实挺拉的。

想法二：Gradient Penalty。

<img src="https://s2.loli.net/2022/07/02/5tfQYTE1ApIj9Zl.png" alt="image-20220702221255324" style="zoom:50%;" />

想法三：Spectral Normalization。





# GAN_P3

有了 WGAN 并不代表说 GAN 就一定特别好 Train。為什麼 GAN 很难被 Train 起来？

事实上 Generator 跟 Discriminator，它们是互相砥砺才能互相成长的，只要其中一者发生什麼问题停止训练，另外一者就会跟著停下训练。

## Conditional Generation

到目前為止我们讲的 Generator，它输入都是一个随机的分布而已，那这个不见得非常有用。

我们现在想要更进一步的是，我们可以操控 Generator 的输出，我们给它一个 Condition x，让它根据 x 跟 z 来產生 y，那这样的 Conditional Generation。

<img src="https://s2.loli.net/2022/07/02/IRunVTbEJ5xdNUW.png" alt="image-20220702222211000" style="zoom:50%;" />

普通的 ==GAN== 不也是一个标量一个向量输入？

如果要做文字对图片的生成，它其实是一个 Supervised Learning 的问题。你需要一些 Label 的 Data，比如说红眼睛的人头像，才能够训练这种 Conditional 的 Generation。

所以在这样的任务裡面，我们的 x 就是一段文字。比如说输入 Red Eyes，然后机器就可以画一个红眼睛的角色，但每次画出来的角色都不一样。

也许你就可以去把 Generator 训练出来，但这样的方法是错误的。因为这样的 Generator 它只要產生清晰的图片，就可以骗过 Discriminator 了，它何必要去管 Input 文字叙述是什麼。

所以在 Conditional GAN 裡面， Discriminator 不是只吃图片 y，它还要吃 Condition x。

<img src="C:%5CUsers%5Cysc%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5Cimage-20220702222850921.png" alt="image-20220702222850921" style="zoom:50%;" />



那怎麼样训练这样的 Discriminator ？那你需要文字跟影像成对的资料，所以 Conditional GAN 一般的训练需要的 Data 的，是需要有标註的资料的。

光是这样子的 Positive Sample 还不够，还有 Negative Sample，即產生好的图片文字叙述配不上的状况。

再考虑 Image To Image 的情形，只是从影像產生影像,把文字的部分用影像取代掉而已。文献上如果你要做到最好，往往就是 GAN 跟 Supervised Learning，同时使用。

此外，输入的 label 也可以是 multi-label 的。



# GAN_P4 Learning from Unpaired Data

最后讲一个GAN的神奇应用，它把GAN用在==unsupervised Learning==。

我们可能会遇到一个状况：我们有一堆 X 我们有一堆 Y，但 X 跟 Y 是不成对的。这叫做==unlabeled==的资料。

<img src="https://s2.loli.net/2022/07/02/YJeNnvA8OHcTklV.png" alt="image-20220702223725028" style="zoom:50%;" />



我们这边举一个例子：影像风格转换。X domain 是真人的照片，Y domain的图是二次元人物的头像。这个例子没有任何的成对的资料。

解决办法：Unsupervised Conditional Generation。

<img src="https://s2.loli.net/2022/07/02/txUk6CiOclPKSsZ.png" alt="image-20220702224026202" style="zoom:50%;" />

输入是一个 Gaussian 的分佈，输出可能是一个复杂的分佈。现在我们在稍微转换一下我们的想法，输入说是 X domain 的图片的分佈，输出说是 Y domain 的图片的分佈。

把输入改成  X domain 很简单，不从高斯分布里采样就行。那怎麼让输出变成是Y domain 的 distribution 呢？

那就要两三个 discriminator，那这个 discriminator 给它看过很多 Y domain 的图，所以它能够分辨 Y domain 的图跟不是 Y domain 的图。

<img src="https://s2.loli.net/2022/07/03/xPShuYeZ5q1Fg9y.png" alt="image-20210524140458705" style="zoom:50%;" />

但这样不够，还得保证生成的二次元头像跟输入的真实的照片有关联。

<img src="https://s2.loli.net/2022/07/03/GZDRuk1986sXVa3.png" alt="image-20210524141004712" style="zoom:50%;" />



由于没有成对数据，因此无法直接套用 conditional GAN 的想法。因為在 conditional GAN 裡面，我们是有成对的资料来训练 discriminator 的。



## Cycle GAN

这边这个想法叫做==Cycle GAN==。在Cycle GAN裡面会 train 两个 generator。

<img src="https://github.com/unclestrong/DeepLearning_LHY21_Notes/blob/master/Notes_pic/image-20210524141830620.png?raw=true" alt="image-20210524141830620" style="zoom:50%;" />

在训练的时候增加了一个额外的目标：希望输入一张图片，从 X domain 转成 Y domain 以后，要从Y domain转回原来的。我们要让原图和还原的图越相近越好。这叫做 ==Cycle的consistency==。

两张图片本质上就是两个向量，它们之间的距离越接近越好，就是要两张图片越像越好。

所以现在这边我们有三个Network：

1. 第一个generator,它的工作是把X转成Y
2. 第二个generator,它的工作是要把Y还原回原来的X
3. 那这个discriminator,它的工作仍然是要看,蓝色的这个generator它的输出,像不像是Y domain的图

这时你可能会有的一个问题就是：你只能保证两个 domain 的图有关系，但这种关系真的有意义？比如两个 generator 学到的都是图片反转，同样也能保证 cycle consistency。这个问题实际上一般不出现。

Cycle GAN 可以是双向的。

<img src="https://s2.loli.net/2022/07/02/pMnYJsVlE2v49yf.png" alt="image-20220702225831039" style="zoom:50%;" />



一些其他的 GAN。Disco GAN、Dual GAN 跟 Cycle GAN 没什么不同。

相比只能在两种风格间转换的 Cycle GAN，StarGAN 可以做多风格影像风格转换。

一些其他应用：把长的文章变成简短的摘要；翻译；非督导式的语音辨识。



## Evaluation of Generation

要评估 Generator 的好坏完全用人来看显然有很多的问题。应该来点客观的方法。

比如跑一个影像的分类系统：把你的 GAN 產生出来的图片，丢到一个的影像的分类系统裡面，看它產生什麼样的结果。

<img src="https://s2.loli.net/2022/07/02/Dl2ynLFCiBHk1c3.png" alt="image-20220702230658786" style="zoom:50%;" />



如果四不像，那就是均匀分布力。

### Diversity - Mode Collapse

但是光用这个评估的方法会被一个叫做 ==Mode Collapse== 的问题骗过去。

<img src="https://s2.loli.net/2022/07/02/oSnfjz1grKa6QA4.png" alt="image-20220702230818845" style="zoom:50%;" />



这会导致 Generative Model 输出来的图片来来去去就是那几张可能单一的图片。

那為什麼会有 Mode Collapse 这种现象发生？直觉上理解，这个地方就是 Discriminator 的一个盲点，发现这个盲点后每次都整这一出。

### Diversity - Mode Dropping

但是有另外一种更难被侦测到的问题叫做 ==Mode Dropping==。

Mode Dropping 的意思是说，你的產生出来的资料，但看起来多样性好像也够。

这种问题难以侦测。一种可能的方法：

借助我们的 Image Classifier。比如把 Generator 產生 1000 张图片，把这 1000 张图片裡,都丢到 Image Classify 裡面，看输出是哪个 class。

每张图片，都会给我们一个 Distribution。把所有图片的 Distribution 加起来平均，如果很集中说明多样性不行。

Diversity 跟 Quality 好像是有点互斥？实则不然。二者评估范围不同。Quality 是只看一张图片的分布，而 Diversity 看的是一堆图片它分布的平均。

过去有一个非常常被使用的分数,叫做 ==Inception Score==。如果 Quality 高，那个 Diversity 又大，那 Inception Score 就会比较大。

### Fréchet Inception Distance (FID)

还有一个 Evaluation 的 Measure,叫 ==Fréchet Inception Distance==。

<img src="C:%5CUsers%5Cysc%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5Cimage-20220702233919606.png" alt="image-20220702233919606" style="zoom:50%;" />

你先把你產生出来的二次元的人物，丢到 Inception Net 裡面，那个 Inception Network 输出它的类别，那你得到的可能就是人脸，那每一张二次元的人物看起来都是人脸，那我们不要拿那个类别。

我们拿进入 Softmax 之前的 Hidden Layer 的输出。把这个向量拿出来代表这张图片。

我们拿出来的是一个向量，而不是最后的类别。那虽然最后分类的类别可能是一样的，但是在决定最后的类别之前，这个向量就算都是人脸，可能还是不一样的。

假设真实的图片跟產生出来的图片它们都是 Gaussians 的 Distribution，然后去**计算这两个 Gaussians Distribution 之间的==Fréchet  Distance==**。因為它是一个 Distance，所以这个值就是越小越好，代表这两组图片越接近。

但实际上图片不一定是 Gaussians Distribution，且要準确得到你的 Network 它的分布需要產生大量的 Sample 才能做到。



