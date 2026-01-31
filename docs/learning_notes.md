
# 📝 ROS学习笔记

## 第一阶段：环境与基础（第1-2周）


### 2026-01-31 ：ROS节点
**学习内容**: ROS节点编程练习

**关键收获**:
1.ROS节点的创建和初始化流程
2.编写一个完整的发布者节点程序
3.消息发布频率
4.ROS日志系统与普通输出的区别

**命令记录**:
# 编译
cd ~/catkin_ws
catkin_make
source devel/setup.bash
# 运行
roscore &
rosrun my_first_package main_node

**遇到的问题**:
- 问题：编译时报错"找不到ros/ros.h"
- 解决：需要在CMakeLists.txt中添加依赖，并运行source /opt/ros/noetic/setup.bash

- 问题：节点启动后按“Ctrl+C”无法终止程序
- 解决：把主循环的条件从while(true)g改为while(ros::ok())

**明日计划**：
编写订阅者节点，完善话题通信示例
学习服务(Service)通信模式



### 2026-01-19 ：环境安装

**学习内容**: ROS Noetic + Gazebo 安装  

**关键收获**:
1. WSL2安装Ubuntu 20.04
2. 安装ROS 和 Gazebo
3. ROS软件源配置的注意事项
4. 工作空间创建与环境变量设置

**命令记录**:
# ROS Noetic安装
sudo apt install ros-noetic-desktop-full

# 创建工作空间的标准流程
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin_make
source devel/setup.bash

**遇到的问题**:
- 问题：Gazebo启动时报GLX错误 
- 解决方案：在WSL2中配置X11转发，使用`export LIBGL_ALWAYS_INDIRECT=1`
    
**明日计划**：
继续学习话题（Topic）通信的概念，演示 "小乌龟轨迹绘制" 。
