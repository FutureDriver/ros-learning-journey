cmake_minimum_required(VERSION 3.0.2)
project(my_turtle_draw)

# 寻找依赖包
find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  turtlesim
  std_srvs
  std_msgs
)

# 声明catkin包
catkin_package()

# 包含目录
include_directories(
  ${catkin_INCLUDE_DIRS}
)

# 添加可执行文件
add_executable(draw_heart_node src/draw_heart.cpp)
target_link_libraries(draw_heart_node ${catkin_LIBRARIES})

#add_executable(window_test src/window_test.cpp)
#target_link_libraries(window_test ${catkin_LIBRARIES})

# 可选：添加之前的版本
# add_executable(simple_heart_node src/simple_heart.cpp)
# target_link_libraries(simple_heart_node ${catkin_LIBRARIES})

# 安装规则
#install(TARGETS draw_heart_down_node window_test
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)
