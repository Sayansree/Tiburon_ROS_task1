#include "ros/ros.h"
#include "std_msgs/Int32.h"

int ans=0;
void recv(const std_msgs:Int32 data)
{
  ROS_INFO("actual ans: %d", msg->data);
  ans=msg->data;
}
void check(const std_msgs:Int32 data)
{
  ROS_INFO("received ans: %d", msg->data);
  cout<<(ans==(msg->data))?"correct ans":"false answer";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node3");
  ros::NodeHandle N;
  ros::Subscriber ch2 = N.subscribe("channel2", 1000, check);
  ros::Subscriber ch3 = N.subscribe("channel3", 1000, recv);
  ros::spin();

  return 0;
}
