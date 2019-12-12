#include "ros/ros.h"
#include "std_msgs/Int32.h"

#include <sstream>

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "node1");
  ros::NodeHandle N;
  ros::Publisher ch1 = N.advertise<std_msgs::Int32>("channel1", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Int64 n;
    n.data = count;
    ROS_INFO("sent: %d", n.data);
    ch1.publish(n);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}