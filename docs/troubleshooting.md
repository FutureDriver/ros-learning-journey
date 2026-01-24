# 问题排查记录



## Git相关

### 问题：fatal: not a git repository
**错误信息**：
fatal: not a git repository (or any of the parent directories): .git
**原因**：当前目录未初始化Git仓库
**解决方案**：
git init
git remote add origin https://github.com/FutureDriver/ros-learning-journey.git



## ROS环境相关

### 问题: Command 'roscore' not found
**原因**: ROS环境变量未设置
**解决方案**:

# 临时设置
source /opt/ros/noetic/setup.bash

# 永久设置
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

### 问题: Package 'my_first_package' not found
**原因**: 工作空间环境未设置
**解决方案**:

cd ~/catkin_ws
source devel/setup.bash

# 永久设置
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc



## 编译相关

### 问题: catkin_make 编译失败
**常见原因**:
1. CMakeLists.txt语法错误
2. 依赖包未安装
3. 文件权限问题
**解决方案**:

# 清理后重新编译
cd ~/catkin_ws
rm -rf build devel
catkin_make



## ROS编译相关

### 问题：catkin_make找不到包
**错误信息**：
CMake Error at /opt/ros/noetic/share/catkin/cmake/catkinConfig.cmake:83 (find_package):
  Could not find a package configuration file provided by "my_package" with
  any of the following names:

**原因**：环境变量未设置或包未正确编译
**解决方案**：

# 重新设置环境
source devel/setup.bash

# 或者重新编译
catkin_make



## WSL2图形显示

### 问题：Gazebo/ turtlesim窗口无法显示

**解决方案**：
1. 在Windows安装X11服务器（如VcXsrv）
2. WSL2中设置：
    export DISPLAY=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2}'):0
    export LIBGL_ALWAYS_INDIRECT=1
    
3. 启动VcXsrv时选择"Disable access control"
   
   
   
## 小乌龟演示

### 问题: 不知道如何打开小乌龟

**解决方案**:
# 需要三个终端
# 终端1: 启动ROS核心
        roscore

# 终端2: 启动小乌龟仿真器
        rosrun turtlesim turtlesim_node

# 终端3: 启动键盘控制
        rosrun turtlesim turtle_teleop_key

**调试命令**:

# 查看运行的节点
rosnode list

# 查看活跃的话题
rostopic list

# 查看节点通信图
rqt_graph
