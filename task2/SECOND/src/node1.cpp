#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include <sstream>
#include <vector>
#include <string>

int main(int argc, char **argv)
{
  std::vector<std::string> que ;
  que.push_back(" question a ... options\na...\nb...\nc...\nd...\n");
  que.push_back(" question b ... options\na...\nb...\nc...\nd...\n");
  que.push_back(" question c ... options\na...\nb...\nc...\nd...\n" };
  std::vector<int> ans;
  ans.push_back(0);
  ans.push_back(1);
  ans.push_back(4);
  ros::init(argc, argv, "node1");
  ros::NodeHandle N;

  ros::Publisher ch1 = N.advertise<std_msgs::String>("channel3", 1000);
   ros::Publisher ch3 = N.advertise<std_msgs::Int32>("channel1", 1000);
  ros::Rate loop_rate(0.5);


  while (ros::ok()&!que.empty())
  {
    std_msgs::Int32 n;
    std_msgs::String msg;
    std::stringstream ss;
    ss << que.back();
    msg.data = ss.str();
    n.data = ans.back();
    ROS_INFO("sent: %d\t%s", n.data,msg.data.c_str());
    ch3.publish(n);
    ch1.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    que.pop_back();
    ans.pop_back();
  }
  return 0;
}
