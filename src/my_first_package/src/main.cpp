//main.cpp
#include <ros/ros.h>                 // ROS核心头文件，包含ROS系统所有基本功能
#include <std_msgs/String.h>         // ROS标准消息类型中的字符串消息头文件

int main(int argc, char **argv)      // 标准C++ main函数入口，接收命令行参数
{
    // Initialize the ROS node
    ros::init(argc, argv, "main");   // 初始化ROS节点，注册节点名为"main"
    ros::NodeHandle nh;              // 创建节点句柄，管理节点资源和通信
    

    printf("Hello World from main.cpp!\n");  // 普通C++输出，不会出现在ROS日志系统
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 10);
    ros::Rate loop_rate(1); // 1 Hz - 设置循环频率为每秒1次

    // Main loop
    while (ros::ok())  // 检查ROS系统是否正常运行（没被Ctrl+C终止）
    {
        std_msgs::String msg;           // 创建消息对象
        msg.data = "Hello from main!";  // 填充消息内容
        pub.publish(msg);               // 发布消息到"chatter"话题
        ROS_INFO("Published: %s", msg.data.c_str());  // ROS日志输出

        ros::spinOnce();      // 处理一次回调（如果有订阅者回调函数）
        loop_rate.sleep();    // 休眠以达到指定的循环频率
    }
    
    return 0;  // 程序退出
}
