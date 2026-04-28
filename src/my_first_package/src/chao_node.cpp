//chao_node.cpp
#include <ros/ros.h>                 // ROS核心头文件，包含ROS系统所有基本功能
#include <std_msgs/String.h>         // ROS标准消息类型中的字符串消息头文件

int main(int argc, char **argv)      // 标准C++ main函数入口，接收命令行参数
{
    ros::init(argc, argv, "chao_node");  // 初始化ROS节点，节点名为chao_node
    ros::NodeHandle nh;              // 创建节点句柄，nh对象用于与ROS系统进行通信

    ros::Publisher pub = nh.advertise<std_msgs::String>("kuai_shang_che_kai_hei_qun", 10);

    ros::Rate loop_rate(10);

    while(ros::ok())
    { 
        printf("我要开始刷屏了！\n");
        std_msgs::String msg;
        msg.data = "国服马超，带飞";
        pub.publish(msg);
        loop_rate.sleep();
        ros::spinOnce();
    }
        return 0;  // 程序退出
}
