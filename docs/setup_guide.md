# 🛠️ 环境配置与复现指南

本文档详细记录了如何从零开始复现此项目。

## 系统要求
- 操作系统：Ubuntu 20.04 (推荐使用WSL2或虚拟机)
- 建议配置：≥4核CPU、≥8GB内存、≥50GB硬盘
- 网络: 需要访问GitHub和ROS官方源

## 详细安装步骤

### 1. ROS Noetic 安装

 1.1 设置软件源
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

 1.2 设置密钥
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

 1.3 安装ROS
sudo apt update
sudo apt install ros-noetic-desktop-full

 1.4 初始化
sudo rosdep init
rosdep update

 1.5 创建工作空间目录
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws

 1.6 编译工作空间
catkin_make

 1.7 环境设置
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc


### 2. 验证安装

 2.1 测试ROS核心
roscore &

 2.2 测试小乌龟（可选）
rosrun turtlesim turtlesim_node
 在另一个终端运行：
rosrun turtlesim turtle_teleop_key


### 3. 获取本项目并编译

 3.1 克隆仓库
git clone https://github.com/FutureDriver/ros-learning-journey.git ~/catkin_ws

 3.2 进入工作空间
cd ~/catkin_ws

 3.3 编译所有包
catkin_make


## WSL2特殊配置

### 4.1 图形界面显示

Windows端需要安装X11服务器：

 1 **安装VcXsrv**（或其他X11服务器）
    
 2 **配置WSL2环境**：
 添加到~/.bashrc
echo "export DISPLAY=\$(grep nameserver /etc/resolv.conf | awk '{print \$2}'):0" >> ~/.bashrc
echo "export LIBGL_ALWAYS_INDIRECT=1" >> ~/.bashrc
source ~/.bashrc

 3 **启动VcXsrv时**选择"Disable access control"

### 4.2 性能优化

# 在Windows的PowerShell中执行（管理员权限）
wsl --set-version Ubuntu 2
wsl --shutdown


## 环境检查清单
- ROS版本：`rosversion -d` 显示 "noetic"
- 工作空间：`echo $ROS_PACKAGE_PATH` 包含你的工作空间路径
-- `roscore` 可以正常启动
- `turtlesim` 可以显示图形窗口
- Gazebo：`gazebo --version` 能正常显示版本号
    


## 常见配置问题
- **WSL2图形显示问题**：需要安装X11服务器（如VcXsrv）
- **Gazebo无法启动**：可能需要额外的依赖或调整显卡设置
- **权限问题**：使用sudo时注意环境变量的区别
Q: 找不到ROS命令
A: 运行 `source /opt/ros/noetic/setup.bash`

Q: 编译时找不到包
A: 确保在 `catkin_ws` 目录编译，并运行 `source devel/setup.bash`

Q: WSL2中图形不显示
A: 检查X11服务器是否运行，DISPLAY变量是否正确设置


## 🎯 下一步
完成环境配置后，建议按照以下顺序学习：
1. 阅读 [学习笔记](learning_notes.md) 了解基础概念
2. 运行 `my_first_package` 中的示例代码
3. 查看 [问题排查记录](troubleshooting.md) 避免常见错误
