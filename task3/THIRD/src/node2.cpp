#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

 image_transport::Publisher pub;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    int key=-1;
    cv::Mat frame;
  try
  {
    frame = cv_bridge::toCvShare(msg, "bgr8")->image
    cv::imshow("n2",frame );
    key=cv::waitKey(1)&0xff;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    return;
  }
    if(key==27 ||key==13||key=='e')
            ros::shutdown();
    else if(key=='s')
            cv::imwrite( "output.jpg", frame );
    else if (key=='p'):
            pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node2");
  ros::NodeHandle n;
  image_transport::ImageTransport it(n);
  image_transport::Subscriber sub = it.subscribe("cam1", 1, imageCallback);
  pub = it.advertise("cam2", 1);
  cv::namedWindow("n2");
  cv::startWindowThread();
  ros::spin();
  cv::destroyAllWindows();
  return 0;
}
