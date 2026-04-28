#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "map_pub_node");
  ros::NodeHandle nh;
  ros::Publisher map_pub = nh.advertise<nav_msgs::OccupancyGrid>("map", 1);

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    nav_msgs::OccupancyGrid map;

    map.header.frame_id = "map";
    map.header.stamp = ros::Time::now();

    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.resolution = 1.0;
    map.info.width = 4;
    map.info.height = 2;

    map.data.resize(map.info.width * map.info.height);
    map.data[0] = 100;
    map.data[1] = 100;
    map.data[2] = 0;
    map.data[3] = -1;

    map_pub.publish(map);
    ros::spinOnce();
    loop_rate.sleep();
  }

}