## Mavros

---

### 1. mavros 脚本语法

```typescript
<launch>
    <node pkg="功能包的名字" type="功能包下你想启动节点的名字" name="对这个节点再命个名" output="">
    output 结果输出在屏幕上，没有这个参数默认记录在log里
        <param name=""> 传参:https://blog.csdn.net/taste_cyn/article/details/82737225
    </node>
</launch>
```



### 2. mavros 数据传输

关注 px4_pos_estimator.cpp，可能是向飞控传飞机的姿态数据。他们传数据，都是用ros订阅的方式，飞控又是只看得懂mavlink协议里面的东西。所以飞控怎么拿数据呢？

main：先在从t265订阅（subscribe）的消息中，拿到飞机的姿态数据。

![image-20211022151053255](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211022151053255.png)

main：开辟一个话题（advertise），用以表示无人机的位置和姿态。

![image-20211022151133647](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211022151133647.png)

send_to_fcu：利用 publish 将消息发布。

 <img src="C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211022151351191.png" alt="image-20211022151351191" style="zoom:67%;" />

问：mavros 通过订阅和发布实现消息的传输，飞控又遵循的是mavlink协议，所以飞控怎么拿数据呢？

思路：应存在有一部分会发送 mavlink 消息，那收到 mavlink 消息前，有需要先收到 send_to_fcu 发送的 mavros 消息。既然有 publish，那就应该有 subscribe，那怎么找到哪里有 subscribe？

```typescript
grep -r "/mavros/vision_pose/pose"
```

关注 vision_pose_esimate.cpp，该文件订阅了该消息，并将该消息封装成 mavlink 消息发给飞控。



### 3. PX4 & Ardupilot

px4和ardupilot原本是两套独立的开源飞控，各自有软件和硬件。后来ardupilot看中了px4的硬件，就把代码移植到px4上了。所以目前px4和apm主流是运行在一种硬件上的两种软件。各自都是完备的系统。

px4是基于实时操作系统的，传感器采集、导航、控制、存储等等都是单独的应用程序，因此apm的代码也被封装成了一个应用程序，跟px4的代码栈在一起。而且apm还用到了一部分px4的底层应用。

飞控控制的想法：rospy + pymavlink。

虽然pymavlink好像是ardu家的实现，但底层其实有直接做px4兼容映射的。

![f7a2606d23b7c5a61e8fd4e0c930690.png](https://upload-images.jianshu.io/upload_images/23298764-7d83b5f35397ea0c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这些标题下的例程，优先试试。试代码的时候记得不要无脑试，要验证 mavlink 能不能通。看设计痕迹，pymavlink还是有点针对ardupilot的。

https://www.ardusub.com/developers/pymavlink.html
