#!/bin/bash

# 清空所有ros进程
killall -9 roscore 2>/dev/null
killall -9 rosout 2>/dev/null
killall -9 roslaunch 2>/dev/null

# 等待
sleep 1

# 1. 启动roscore
gnome-terminal --tab --title="roscore" -- bash -c "roscore; exec bash"
sleep 2

# 2. 启动turtlesim（最大化窗口）
gnome-terminal --tab --title="turtlesim" -- bash -c "rosrun turtlesim turtlesim_node; wmctrl -r turtlesim -e 0,0,0,800,600; exec bash"
sleep 2

# 3. 清屏并重置位置
rosservice call /clear
rosservice call /turtle1/teleport_absolute 5.5 5.5 0

# 4. 设置画笔颜色（红色）
rosservice call /turtle1/set_pen 255 0 0 5 0

# 5. 运行画心程序
gnome-terminal --tab --title="draw_heart" -- bash -c "rosrun my_turtle_draw draw_heart_simple; exec bash"

echo "所有节点已启动！"
