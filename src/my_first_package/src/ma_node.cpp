//ma_node.cpp
#include <ros/ros.h>
#include <std_msgs/String.h>

void chao_callback(std_msgs::String msg)
{
    ROS_INFO("I heard: [%s]", msg.data.c_str());
    //printf(msg.data.c_str());
    //printf("\n");

    // std::string data = msg.data;
    // ROS_INFO("String length: %zu", data.size());
    // for (size_t i = 0; i < data.size(); ++i) {
    //     printf("%02x ", (unsigned char)data[i]);
    // }
    // printf("\n");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ma_node");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("kuai_shang_che_kai_hei_qun", 10,chao_callback);

    while (ros::ok())
    {
        //处理一次回调（如果有订阅者回调函数）
        //即每隔一段时间，打断手头的事回来看一下有没有新消息包，防止错过新消息包导致回调函数无法响应
        ros::spinOnce();
    }
    
    return 0;
}