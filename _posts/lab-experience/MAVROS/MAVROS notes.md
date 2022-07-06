## MAVROS 教程 —— Offboard 模式下自主飞行

>[AMOV 视频教程](https://bbs.amovlab.com/plugin.php?id=zhanmishu_video:video&mod=video&cid=11)

### 1.1 工具链安装

MAVROS 操作无人机的软硬件架构

![image-20211112101000509](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112101000509.png)

Mavros 工具包可以把接收到的 Mavlink 消息（状态数据）转换成 ROS 消息发送给 ROS 系统，亦可以把 ROS 系统发送的 ROS 消息（控制消息）转换成 Mavlink 消息发送给飞控。

工具链：VMware 虚拟机 + 18.04 Ubuntu + ROS Melodic + mavros 包 + gazebo 仿真工具

ROS 安装

- 换源，如中科大、阿里、清华。vim(gedit) /etc/apt/source.list。
- sudo apt-get update。sudo apt-get update
- [安装](wiki.ros.org/melodic/installation/ubuntu)。最后两行代码容易失败，建议科学上网或者多试几次。
- 检验安装：roscore

Mavros 安装

- 二进制安装：已经编译好的工具

- 源码安装[推荐]：[安装](docs.px4.io/master/en/ros/mavros_installation.html)。都是原始代码，必须编译成可以执行的二进制文件才可以执行，可以修改代码，进行开发等等。注：教程处用的是 kinetic 版本，实际中记得换成 melodic。

- 检验安装：roslaunch mavros px4.launch

  

### 1.2 ROS 创建节点与编译

ROS 的通信方式：

- server 点对点，响应快
- topic 多对多



ROS 文件系统组织

编译基于 catkin，CMakeList.txt 用于后续的编译。

![image-20211112102122959](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112102122959.png)

[常用命令](http://wiki.ros.org/ROS/Tutorials/NavigatingTheFilesystem)

- rospack
  - 获取有关包的信息，本教程仅以 find 为例，返回包的路径。
  - rospack find [pacakge name]
- roscd
  - 将目录改为包或堆栈，或者其子目录
  - roscd \<package-or-stack\>[/subdir]
- rosls
  - 直接查看包中文件，或者其子目录
  - rosls \<package-or-stack\>[/subdir]



节点创建与编译

- 创建工作空间并进入 src。mkdir -p catkin_ws/src，cd catkin_ws/src
- 创建功能包。crakin_create_pkg [package-name] roscpp std_msgs
  - roscpp：用 cpp 编译
  - std_msgs：用已有的数据结构
- 进入功能包的 src 并创建源文件。cd package-name/src。

 <img src="C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112103129639.png" alt="image-20211112103129639" style="zoom: 67%;" />

- 回到上级目录，修改 CMakeLists.txt。
  - ![image-20211112103252704](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112103252704.png)
  - 第一个参数是为生成的可以执行文件定义一个名字，第二个是默认的源代码目录，需要修改。
  - ![image-20211112103454634](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112103454634.png)
  - 第一个参数需要和前者对应。
- 回到工作空间目录，编译。catkin build。会产生 build、devel 文件夹。
- 编译成功后，roscore，source ~/catkin_ws/devel/setup.sh。之后便可 rosrun [结点名]。



### 1.3 ROS 编程基础

例程：简单的发布和订阅

![image-20211112103916004](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112103916004.png)

[代码讲解]

运行方式（注意各个命令用独立的终端）

- roscore
- rosrun minimal_nodes[包名] minimal_publisher[节点名]
- rosrun minimal_nodes[包名] minimal_subscriber[节点名]
- rostopic list，rostopic info topic1[话题名]，rostopic hz topic1[话题名]。

例程：简单的控制器和仿真器

![image-20211112104339826](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112104339826.png)

![image-20211112104410098](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112104410098.png)

[代码讲解]

运行方式

- roscore
- rosrun minimal_nodes[包名] minimal_simulator[节点名]
- rosrun minimal_nodes[包名] minimal_controller[节点名]
- 发送预定速度：rostopic pub -r 10[hz] vel_cmd[话题名] std_msgs/Float64[数据类型] 1.0

C++ 类的使用

ROS代码如果订阅很多个消息，发布多个消息的话，很快会变得过于冗长，若要提高代码效率和代码复用，最好使用类。

在头文件中定义类:

- 定义所有成员函数的原型

- 定义私有和公共数据成员

- 定义构造函数的原型

编写一个单独的实现文件

- 包含上面的头文件
- 包含已经声明成员函数的工作代码
- 包含在构造函数中封装的必要的初始化的代码

构建文件系统

- 在功能包目录下创建一个inlcude/minimal_controller_class [结点名]的文件夹

- 并在该文件夹下创建一个minimal_controller_class.h的文件
- 在src目录下创建minimal_controller_class.cpp文件

修改CMakeLists.txt，使得ros结点包含进include文件夹所包含的头文件

<img src="C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112105212272.png" alt="image-20211112105212272" style="zoom:50%;" />

没看完，先跳过。



### 1.4 Mavros 消息的订阅与发布

1.4.1 应用mavros控制无人机的消息流

- 如何去查阅mavros的消息与mavlink协议之间的关系
- 如何去找到mavlink协议与uorb消息之间的对应关系

![image-20211112105445856](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112105445856.png)





![image-20211112105635483](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112105635483.png)



1.4.2 example offboard例程的仿真与解析

- 使用gazebo进行软件在环仿真
- 搭载机载计算机的无人机的实际飞行测试

![image-20211112112529657](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112112529657.png)

![image-20211112120815187](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112120815187.png)

![image-20211112121128801](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112121128801.png)

![image-20211112121212743](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112121212743.png)

![image-20211112121253406](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112121253406.png)

ENU 坐标系，z=2，升高两米。

![image-20211112122001643](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112122001643.png)

![image-20211112122159260](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112122159260.png)

![image-20211112122300241](C:\Users\ysc\AppData\Roaming\Typora\typora-user-images\image-20211112122300241.png)

