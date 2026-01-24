# 问题排查记录



## Git相关

### 问题：fatal: not a git repository
**错误信息**：
fatal: not a git repository (or any of the parent directories): .git
**原因**：当前目录未初始化Git仓库
**解决方案**：
git init
git remote add origin https://github.com/FutureDriver/ros-learning-journey.git

###问题：Failed to connect to github.com port 443: Connection refused
**错误信息**：
genius@R9000P:~/catkin_ws$ git push -u origin main
fatal: unable to access 'https://github.com/FutureDriver/ros-learning-journey.git/': Failed to connect to github.com port 443: Connection refused
**原因**：（家庭网络、无代理软件）问题很可能出在WSL2的网络虚拟化层面。并且这是一个已知的、特定于某些Windows系统版本的WSL2网络问题
**解决方案**：
1、诊断WSL的网络连通性
测试到GitHub最基本的HTTPS连接 (关键)
curl -v https://github.com   
**系统提示**：
curl: (7) Failed to connect to github.com port 443: Connection refused
**分析**：
系统将 github.com 错误地解析到了本机IP 127.0.0.1，导致所有连接尝试都指向了自己的电脑，因此被拒绝。
这是典型的 DNS劫持/污染。
在家庭网络环境下，最常见的原因是：
/etc/hosts 文件被修改：某些软件（如旧版GitHub加速工具、代理客户端或恶意软件）可能篡改了此文件。
WSL的DNS配置异常：指向了错误或失效的DNS服务器。
**应对措施**：
① 查看hosts文件内容，检查是否有关于github.com的条目
sudo cat /etc/hosts | grep -i github
没有发现

② # 使用编辑器（如nano）打开hosts文件
sudo nano /etc/hosts
没有涉及github.com的信息，说明hosts文件是干净的，没有对github.com的劫持。
这确认了问题出在 WSL2 自身的 DNS 解析层，而不是hosts文件。

③ 确认当前的DNS解析状态：使用nslookup，明确查看github.com被解析成了什么IP
nslookup github.com
找到原因了！WSL2内部DNS代理（10.255.255.254）出现了故障，它将所有域名都错误地解析到了本机 127.0.0.1

④ 修复WSL的DNS配置
阻止WSL自动生成错误的DNS配置
sudo bash -c 'cat > /etc/wsl.conf << EOF
[network]
generateResolvConf = false
EOF'

删除当前错误的DNS配置文件
sudo rm /etc/resolv.conf

设置可靠的公共DNS服务器（推荐谷歌和国内114）
sudo bash -c 'echo "nameserver 8.8.8.8" > /etc/resolv.conf'
sudo bash -c 'echo "nameserver 114.114.114.114" >> /etc/resolv.conf'

锁定resolv.conf文件权限，防止被系统修改（关键步骤）
sudo chattr +i /etc/resolv.conf

⑤ 重启WSL2
在 Windows PowerShell 或 命令提示符（不是WSL内）执行
wsl --shutdown

⑥ 重启后，验证是否修复：
确认DNS配置已更新且被锁定
lsattr /etc/resolv.conf  # 应该显示含有"i"属性（不可修改）
cat /etc/resolv.conf     # 应该显示8.8.8.8和114.114.114.114

测试DNS解析 - 现在应该看到GitHub的真实IP地址（如140.82.113.4）
nslookup github.com

测试HTTPS连接 - 应该成功（返回HTTP/2 200等头信息）
curl -I https://github.com

**问题根源与预防**：
这个问题的根源是WSL2虚拟网络内部的DNS代理（10.255.255.254）在Windows休眠、网络切换或长时间运行后可能崩溃。通过以上配置：
/etc/wsl.conf：告诉WSL不要自动管理DNS。
手动设置公共DNS：绕过不可靠的内部代理。
chattr +i：防止任何程序意外修改你的DNS设置。



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
