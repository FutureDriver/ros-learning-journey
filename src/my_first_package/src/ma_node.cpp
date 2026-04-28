//ma_node.cpp
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <locale>

void chao_callback(std_msgs::String msg)
{
    ROS_INFO("I heard: [%s]", msg.data.c_str());
    //printf(msg.data.c_str());
    //printf("\n");

    //debug:
    // bug现象：ROS_INFO打出的msg内容是一串“???...” → 确认 msg.data 的实际使用编码
    // 方案：打印每个字节的十六进制值,同时输出 printf 直接打印的结果。对比一下中文字符的 UTF-8 编码
    // 确认结果：msg.data 中的内容是 标准的 UTF-8 编码（例如 e5 9b bd 对应“国”）。
    //          printf 能正常打印，说明终端和系统 locale 都支持 UTF-8。
    //          但 ROS_INFO 依然输出问号，说明问题确实出在 ROS 日志系统（log4cxx）内部的编码转换环节，
    //          即使设置了 ROS_CONSOLE_ENCODING=UTF-8 也没有生效。
    //推测：Noetic的log4cxx库中，控制台 appender 的编码被编译时默认的 LC_CTYPE 锁定，
    //     而环境变量 ROS_CONSOLE_ENCODING 可能未被正确传递或覆盖。
    //     当 LC_ALL 或 LC_CTYPE 被设为 C.UTF-8 时，log4cxx 可能仍使用旧的 ASCII 编码，导致非 ASCII 字符变为问号。
    //对策：在代码中设置全局locale，这是最直接、影响范围最小的方案。
    //     原理是显式地将C++程序的全局locale设置为系统的默认locale，
    //     让log4cxx利用这个locale来正确解码UTF-8字符
    //  std::string data = msg.data;
    // ROS_INFO("String length: %zu", data.size());
    // for (size_t i = 0; i < data.size(); ++i) {
    //     printf("%02x ", (unsigned char)data[i]);
    // }
    // printf("\n");
}

int main(int argc, char **argv)
{
    std::locale::global(std::locale("")); 
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