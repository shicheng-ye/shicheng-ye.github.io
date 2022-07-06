---
layout: post
title:  "[review]Reinforcement learning"
date:   2022-07-06 15:09:45 +0800
categories: courses
---



# Reinforcement Learning P1 ：Basics

## Supervised Learning→RL

Supervised Learning：给定 label

Self Supervised Learning：自动生成 label

Unsupervised Learning(Auto-encoder)：没用到人类的 label，但事实上仍然还有 label 只不过不需要用人力生成

RL：机器当我们给它一个输入的时候，我们不知道最佳的输出（label）应该是什么。如下棋。

## Outline

<img src="https://s2.loli.net/2022/07/02/47o2ubILgfhtE6w.png" alt="image-20220702145935497" style="zoom:50%;" />

## Machine Learning ≈ Looking for a Function

机器学习就是找一个 Function，Reinforcement Learning 也是，这个 Function 即 Actor 本身，要做的就是最大化 reward 之总和。

例：Atari Space Invador。Actor：操作对象。环境：游戏场景。Observation：游戏画面。

例：围棋。稀疏 Reward，只有游戏结束（输、赢）才能够拿到 Reward。



## Machine Learning is so simple ……

Machine Learning 三个步骤：

1. 定义含待求未知数的 Function
2. 定义 Loss Function
3. Optimization，minimize loss

而 RL 其实也是一模一样的三个步骤



### Step 1: Function with Unknown 

Function (in RL) = Actor, RL 中的 Actor 即神经网络，通称 Policy 的 Network。

神经网络输入：the observation of machine represented as a vector or a matrix。

神经网络输出：each action corresponds to a neuron in output layer。

![image-20220702151119061](https://s2.loli.net/2022/07/03/nj8qFcTSyQ1RCBM.png)

为什么输出结果是概率分布？引入随机性。

### Step 2: Define “Loss”

从游戏开始到结束的这整个过程被称之为一个 ==Episode==,

将整个游戏的过程中 Actor 採取非常多的行为得到的 Reward 通通集合起来便是 ==Total Reward (Return)==。$R = \sum^{T}_{t=1}r_t$ 。

Return 是最大化的对象，我们要最小化 loss，可以定义 loss = -R。

### Step 3: Optimization 

将整个游戏的过程中 s 跟 a 所形成的这个 Sequence 叫做 Trajectory。符号表示为 $\tau = {s_1, a_1,s_2,a_2,...}$。

通常说，Reward Function 在定义的时候和 Action 与 Observation 都有关联。即 $r_i$ 和 $s_i$  和 $a_i$ 有关系。优化 Return 就行。

但是 RL 困难之处在于它不是一个一般的 Optimization 的问题。

第一个问题是，Actor 的输出是有随机性的。 Network 裡面的某一个 Layer 每次产生出来结果是不一样的。第二，Environment 只是一个黑盒，且包含随机性。

与 GAN 的对比。

相同：GAN 中 调整 Generator 的参数让 Discriminator 的输出越大越好。RL 中调整 ACtor 的参数让 Environment 的 Reward 越大越好。

不同：Discriminator 是 Network，但 Environment 只是个黑盒。不能用 GD 调整 Environment。

# Policy Gradient

### How to control your actor 

<img src="https://s2.loli.net/2022/07/02/v7TwXC5UEJWoGdL.png" alt="image-20220702152953732" style="zoom:50%;" />

可以把它想成一个分类的问题。即 s 是 Actor 的输入, $\hat{a}$(Ground Truth) 就是 Label。

计算 Actor 的输出跟 Ground Truth 之间的 Cross-entropy，那接下来就可以定义一个 Loss。提示：根据交叉熵的定义，预测分布和真实分布有相同的分布时交叉熵最小。Loss 越小，就等价于预测值越接近真实值。

<img src="https://s2.loli.net/2022/07/02/Zb6yw2HEv38tVJM.png" alt="image-20220702153405916" style="zoom:50%;" />

模型训练

<img src="https://s2.loli.net/2022/07/02/T3mxPShAgQp6ZKY.png" alt="image-20220702153533859" style="zoom:50%;" />

用数值 A 表示代替 +1/-1，就可以实现表示动作的好坏程度。Loss 改写为：
$$
L=\sum A_ne_n
$$



## Value Function

## Version 0

用随机的  Actor 去跟环境做互动收集训练资料获得 $\{s_i, a_i\}$。再根据情况好坏为之赋予 $r_i$。

最简单的但不正确的版本。短视近利。事实上，每一个行为都会影响到接下来发生的事情。例：Space Invador 中，由于只有开火才能得到正 Reward，故他会一直开火。

Reward Delay：牺牲短期的利益,以换取更长程的目标。

## Version 1

==Cumulated Reward==：把当下与未来所有的 Reward 加起来评估一个 Action 的好坏。
$$
G_t = \sum^{N}_{n=t} r_n
$$
用 $G_i$ 表示每个 $\{s_i, a_i\}$ 对应的 reward。

问题在于：未来发生的影响中，有些影响大有些影响小。

## Version 2

加上递减权重 $\gamma$。未来的 reward 中，离当下近的表示影响更大。
$$
G'_t = \sum^{N}_{n=t} \gamma^{n-t}r_n
$$

## Version 3

做标准化，因为好或坏是相对的。

一个最简单的方法就是：把所有的 G' 都减掉一个 b，即==Baseline==。

## Policy Gradient 

<img src="https://s2.loli.net/2022/07/03/GJB31Hvkh4InrgR.png" alt="image-20220702155759971" style="zoom:50%;" />

其中，$L = \sum A_n e_n$。$A_n$ 就是 Reward，$e_n$ 就是交叉熵。

一般的 Training，Data Collection 都是在 For 循环之外。但在 RL 裡面收集资料是在 For 循环裡面。这意味着更新一次参数以后，就要重新收集资料，因此 RL 的训练过程非常花时间。

为什么不把 Data Collection 放在 For 循环之外？彼之砒霜，吾之蜜糖。因为由 $θ_{i-1}$ 所收集出来的资料不一定适合拿来 Update $θ_{i}$ 的参数。

故同一个 Action 同一个行为，对于不同的 Actor 而言，它的好是不一样的。更新后的 Actor，可能 Trajectory 就会跟之前出现区别。



### On-policy v.s. Off-policy

被训练的 Actor 与跟环境互动的 Actor 是同一个叫做 ==On-policy  Learning==。

反之，为 ==Off-policy Learning==。

Off-policy 的好处：不用一直收集资料。可以收一次资料，就 Update 参数很多次。

显然上文所述为 On-policy Learning。



### Off-policy → Proximal Policy Optimization(PPO)

Off-policy 的经典算法： Proximal Policy Optimization。

Off-policy 的重点：在训练的那个 Network，要知道自己跟别人之间的差距，它要有意识到它跟环境互动的那个 Actor 是不一样的。

例子：东施效颦，别瞎模仿。



### Collection Training Data: Exploration 

Exploration：Actor 在採取行为的时候有随机性的。随机性大一点意味着能够收集到比较丰富的资料。实现方法：增大 Actor 的 Output（Distribution）的 Entropy；在 Actor 参数上加 Noise。



## Critic

Critic 用以评估一个 Actor 的好坏。Given actor 𝜃, how good it is when observing 𝑠 (and taking action 𝑎)。

本课程中 Critic 叫做 ==Value Function==，用 $V^θ(s)$ 来表示。输出一个 scalar（Discounted Cumulated Reward）。

故 Value Function 的作用就是：对某一个参数为 $\theta$ 的 Actor 来说，如果它已经看到某一个游戏画面 s，那接下来会得到的 Discounted Cumulated Reward 应该是多少。

DCR 需要未来的 Reward 来计算。但当下怎么知道未来的 Reward 呢？Value Function 的能力就是要未卜先知。



## How to estimate $ V^θ(s) $

### Monte-Carlo (MC) based approach

MC：把 Actor 拿去跟环境互动很多轮，可以得到每轮的 DCR。

那么 Value Function 就得到一笔训练资料，训练目标是：如果看到 $s_a$ 作为输入，那它的输出 $ V^θ(s_a) $ 应该要跟 G'a 越接近越好。

<img src="https://s2.loli.net/2022/07/02/jz5FaG1xdcvsWI7.png" alt="image-20220702161849346" style="zoom: 50%;" />



### Temporal-difference (TD) approach 

一轮互动可能无法终止或者很长。

TD：不用玩完整场游戏，才能得到训练 Value 的资料。虽然我们不知道，$ V^θ(s_t)$ 和 $ V^θ(s_{t+1})$ 应该是什么，但是我们可以让 $ V^θ(s_t)$  与 $ \gamma V^θ(s_{t+1})$ 的差值逼近已知的 $r_t$。

<img src="https://s2.loli.net/2022/07/02/lazNsUr4dnBRx1k.png" alt="image-20220702162248677" style="zoom:50%;" />

### MC v.s. TD

<img src="https://s2.loli.net/2022/07/03/SrMDN6TPgmFfh7v.png" alt="image-20220702162905728" style="zoom:50%;" />



## Version 3.5

把 baseline 设成 $V^θ(S)$。把 $\{s_t,a_t\}$ 对应的 Value 定义为：
$$
A_t = G'_t-V^θ(s_t)
$$
为什么这样可以？我们知道 $ V^θ(s_t)$是看到某一个画面 $s_t$ 以后，接下来会得到的 (加权) Reward。它其实是一个期望，因为有随机性，即每次的 $a_t$ 可能不同，故每次可能会得到不一样的 Reward。

<img src="https://s2.loli.net/2022/07/02/krBqTm6nCYiFKMG.png" alt="image-20220702163444448" style="zoom:50%;" />

图中 Gt' 是 sample 某一个 trajectory 的结果，而$ V^θ(s_t)$ 是很多条路径平均以后的结果。

问题在于：把一个 sample 去减掉平均，这样会准吗？也许这个sample 特别好或特别坏。为什麽不是拿平均去减掉平均？

## Version 4

最后一个版本：平均去减掉平均。这就是 ==Advantage Actor-Critic==。

把 $\{s_t,a_t\}$ 对应的 Value 定义为：
$$
A_t = r_t+V^θ(s_{t+1})-V^θ(s_t)
$$
<img src="https://s2.loli.net/2022/07/03/M72tBQOvFV5lpsX.png" alt="image-20220702163949638" style="zoom:50%;" />



## Tip of Actor-Critic

Actor 和 Critic 都是 Network，他们的输入可以公用 CNN。



## Sparse Reward

Sparse Reward：$r_t$ = 0 in most cases。例如拧螺丝。

解决办法：reward shaping。



## Imitation Learning

Actor 可以与环境互动，但 reward function 不知道怎么定义。

解决办法：根据专家的演示 $\{\hat{\tau_1}, \hat{\tau_2}, ...\}$ 进行模仿学习。

例子：自动驾驶，机械臂抓举。

问题：专家们只对有限的观察进行抽样。



## Inverse Reinforcement Learning

使用 reward function 找到最佳 actor。

原则：The teacher is always the best。

方法论：

<img src="https://s2.loli.net/2022/07/02/YR12xlTz8PwE7sG.png" alt="image-20220702164853222" style="zoom:50%;" />

<img src="https://s2.loli.net/2022/07/02/FDgLe1CdnYfmhoU.png" alt="image-20220702165029388" style="zoom:50%;" />

和 GAN 的类比理解

GAN 中 Generator 的优化目标是产生跟 Ground Truth 的很像的结果，IRL 中 Actor 的优化目标是产生跟 Expert 的很像的结果。

GAN 中 Discriminator 的优化目标是产生分辨 Ground Truth 和 Generator 的输出值，给 Ground Truth 打高分，IRL 中 Reward 则是给 Expert 打高分。

