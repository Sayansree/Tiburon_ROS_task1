#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
int Hmin,Hmax,Smin,Smax,Vmin,Vmax;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{int key=-1;
    cv::Mat frame,output,mask,HSV;
  try
  {
    frame = cv_bridge::toCvShare(msg, "bgr8")->image;  
    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
    cv::Scalar minHSV = cv::Scalar(Hmin,Smin,Vmin); 
    cv::Scalar maxHSV = cv::Scalar(Hmax,Smax,Vmax); 
  
    cv::inRange(HSV, minHSV, maxHSV, mask);
    cv::bitwise_and(frame, brightHSV, output, mask);
    cv::imshow("n2",output );
    key=cv::waitKey(10)&&0xff;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    return;
  }
    if(key==27||key==13)
            ros::shutdown();
    else if(key=='s')
            cv::imwrite( "output.jpg", output);
}
static void ch(int, void*)
{
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "node3");
  ros::NodeHandle nh;
  cv::namedWindow("n3");
  cv::startWindowThread();
   cv::createTrackbar( "H min","n3", &Hmin,180, ch );
   cv::createTrackbar( "H max","n3", &Hmax,180, ch );
   cv::createTrackbar( "S min","n3", &Smin,255, ch );
   cv::createTrackbar( "S max","n3", &Smax,255, ch );
   cv::createTrackbar( "V min","n3", &Vmin,255, ch );
   cv::createTrackbar( "V max","n3", &Vmax,255, ch );
  ch(0,0);
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("cam2", 1, imageCallback);
  ros::spin();
  cv::destroyAllWindows();
}
