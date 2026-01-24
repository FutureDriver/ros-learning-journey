
# 📝 ROS学习笔记

## 第一阶段：环境与基础（第1-2周）




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
