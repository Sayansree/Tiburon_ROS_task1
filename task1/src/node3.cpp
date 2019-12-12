#include "ros/ros.h"
#include "std_msgs/Int32.h"

void recv(const std_msgs:Int32)
{
  ROS_INFO("received: %d", msg->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node3");
  ros::NodeHandle N;
  ros::Subscriber ch2 = N.subscribe("channel2", 1000, recv);
  ros::spin();

  return 0;
}