/**
 * draw_heart.cpp
 * 控制 turtlesim 中的小乌龟画一个爱心
 * 编译: catkin_make 或 g++ 手动编译
 * 运行: rosrun <my_turtle_draw> draw_heart_node
 */


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <cmath>
#include <iostream>
#include <std_srvs/Empty.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>

// 全局变量存储当前姿态
turtlesim::Pose current_pose;

// 姿态回调函数
void poseCallback(const turtlesim::Pose::ConstPtr& msg) {
    current_pose.x = msg->x;
    current_pose.y = msg->y;
    current_pose.theta = msg->theta;
}

// 角度差计算（归一化到[-π, π]）
double normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2 * M_PI;
    while (angle < -M_PI) angle += 2 * M_PI;
    return angle;
}

int main(int argc, char **argv) {
    // 初始化ROS节点
    ros::init(argc, argv, "draw_heart_down_node");
    ros::NodeHandle nh;
    
    ROS_INFO("开始初始化...");
    
    // 创建发布器和订阅器
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Subscriber pose_sub = nh.subscribe("/turtle1/pose", 10, poseCallback);
    
    // 等待连接建立
    ros::Duration(2.0).sleep();
    
    // 初始化服务客户端
    ros::ServiceClient clear_client = nh.serviceClient<std_srvs::Empty>("/clear");
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    
    // 等待服务可用
    clear_client.waitForExistence();
    teleport_client.waitForExistence();
    pen_client.waitForExistence();
    
    ROS_INFO("服务连接成功，开始设置初始状态...");
    
    // 1. 清屏
    std_srvs::Empty clear_srv;
    clear_client.call(clear_srv);
    
    // 2. 设置画笔（红色，线宽3）
    turtlesim::SetPen pen_srv;
    pen_srv.request.r = 255;
    pen_srv.request.g = 0;
    pen_srv.request.b = 0;
    pen_srv.request.width = 3;
    pen_srv.request.off = 0;  // 0=画线，1=不画线
    pen_client.call(pen_srv);
    
    // 3. 计算心形参数和起始位置
    // 窗口参数
    double window_center_x = 5.544445;
    double window_center_y = 5.544445;
    
    // 心形线参数方程（尖朝下）：
    // x = 16 * sin^3(t)
    // y = -(13 * cos(t) - 5 * cos(2t) - 2 * cos(3t) - cos(4t))
    
    // 计算t=0时的位置作为起始点
    double t = 0.0;
    double scale = 0.18;  // 经过计算的缩放因子，确保在窗口内
    
    double start_x = scale * 16 * pow(sin(t), 3);
    double start_y = scale * -(13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t));
    
    // 转换为窗口坐标
    double target_start_x = window_center_x + start_x;
    double target_start_y = window_center_y + start_y;
    
    // 4. 移动到起始点（抬起画笔）
    turtlesim::SetPen pen_up_srv = pen_srv;
    pen_up_srv.request.off = 1;  // 抬起画笔
    pen_client.call(pen_up_srv);
    
    turtlesim::TeleportAbsolute teleport_srv;
    teleport_srv.request.x = target_start_x;
    teleport_srv.request.y = target_start_y;
    teleport_srv.request.theta = 0;  // 初始朝向
    teleport_client.call(teleport_srv);
    
    // 5. 放下画笔开始绘制
    pen_client.call(pen_srv);  // 放下画笔
    
    ROS_INFO("开始绘制尖朝下的心形...");
    ROS_INFO("起始点: (%.2f, %.2f)", target_start_x, target_start_y);
    
    // 6. 控制参数
    ros::Rate rate(40);  // 40Hz控制频率
    double dt = 0.05;    // 参数t的步长
    t += dt;  // 从下一个点开始
    
    // 7. 主循环：绘制心形
    while (t < 2 * M_PI && ros::ok()) {
        // 计算心形线上的目标点
        double raw_x = 16 * pow(sin(t), 3);
        double raw_y = -(13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t));  // 负号使心形尖朝下
        
        // 缩放并平移到窗口中心
        double target_x = window_center_x + scale * raw_x;
        double target_y = window_center_y + scale * raw_y;
        
        // 检查是否在窗口范围内
        if (target_x < 0.5 || target_x > 10.5 || target_y < 0.5 || target_y > 10.5) {
            ROS_WARN("警告: 点(%.2f, %.2f)接近窗口边界!", target_x, target_y);
        }
        
        // 计算当前位置到目标点的向量
        double dx = target_x - current_pose.x;
        double dy = target_y - current_pose.y;
        double distance = sqrt(dx*dx + dy*dy);
        
        // 计算目标角度
        double target_angle = atan2(dy, dx);
        double angle_error = normalizeAngle(target_angle - current_pose.theta);
        
        // 创建速度控制消息
        geometry_msgs::Twist twist_msg;
        
        // P控制器：根据角度误差调整速度和转向
        if (fabs(angle_error) > 0.5) {  // 角度误差大，先转向
            twist_msg.linear.x = 0.1;  // 低速前进
            twist_msg.angular.z = 1.2 * angle_error;
        } else if (fabs(angle_error) > 0.2) {  // 中等角度误差
            twist_msg.linear.x = std::min(0.8, distance * 1.5);
            twist_msg.angular.z = 0.8 * angle_error;
        } else {  // 角度误差小，主要前进
            twist_msg.linear.x = std::min(1.2, distance * 2.0);
            twist_msg.angular.z = 0.3 * angle_error;
        }
        
        // 速度限制
        if (twist_msg.linear.x > 1.2) twist_msg.linear.x = 1.2;
        if (twist_msg.linear.x < 0.0) twist_msg.linear.x = 0.0;
        if (twist_msg.angular.z > 2.0) twist_msg.angular.z = 2.0;
        if (twist_msg.angular.z < -2.0) twist_msg.angular.z = -2.0;
        
        // 发布控制指令
        vel_pub.publish(twist_msg);
        
        // 调试信息（每0.5秒输出一次）
        static double last_print_time = 0;
        double current_time = ros::Time::now().toSec();
        if (current_time - last_print_time > 0.5) {
            ROS_INFO("进度: %.1f%%, 位置: (%.2f, %.2f), 目标: (%.2f, %.2f)", 
                    t/(2*M_PI)*100, current_pose.x, current_pose.y, target_x, target_y);
            last_print_time = current_time;
        }
        
        // 更新参数
        t += dt;
        
        // 控制循环
        rate.sleep();
        ros::spinOnce();
    }
    
    // 8. 绘制完成，回到起始点附近形成闭合
    ROS_INFO("心形主体绘制完成，准备闭合...");
    
    // 抬起画笔，移动到起始点
    pen_up_srv.request.off = 1;
    pen_client.call(pen_up_srv);
    
    teleport_srv.request.x = target_start_x;
    teleport_srv.request.y = target_start_y;
    teleport_srv.request.theta = 0;
    teleport_client.call(teleport_srv);
    
    // 停止运动
    geometry_msgs::Twist stop_msg;
    vel_pub.publish(stop_msg);
    
    ROS_INFO("尖朝下的心形绘制完成！");
    
    // 保持节点运行一段时间
    ros::Duration(2.0).sleep();
    
    return 0;
}
