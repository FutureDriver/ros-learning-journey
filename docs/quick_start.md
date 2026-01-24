# 🚀 快速开始指南

针对已经熟悉ROS的用户，1分钟快速体验

## 克隆并编译
git clone https://github.com/FutureDriver/ros-learning-journey.git ~/catkin_ws
cd ~/catkin_ws && catkin_make
source devel/setup.bash

## 运行小乌龟绘图演示(开3个终端分别执行)
roscore 
rosrun turtlesim turtlesim_node
rosrun my_turtle_draw draw_heart_node


## 包说明
- `my_first_package`: ROS核心概念学习包
- `my_turtle_draw`: 小乌龟绘图演示包

## 学习路径
1. 阅读 `docs/learning_notes.md` 了解学习历程
2. 查看 `docs/setup_guide.md` 获取详细配置
3. 如有问题参考 `docs/troubleshooting.md`

## 扩展学习
1. 尝试修改 `my_turtle_draw` 绘制不同图形
2. 在 `my_first_package` 中添加新功能
3. 阅读ROS官方文档深入学习
