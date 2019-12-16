#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
int Rmin,Rmax,Gmin,Gmax,Bmin,Bmax;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    int key=-1;
    cv::Mat frame,output,mask;
  try
  {
    frame = cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::Scalar minBGR = cv::Scalar(Bmin,Gmin,Rmin) ;
    cv::Scalar maxBGR = cv::Scalar(Bmax,Gmax,Rmax) ;
  
    cv::inRange(frame, minBGR, maxBGR, mask);
    cv::bitwise_and(frame, frame, output, mask);
    cv::imshow("n2",output );
    key=cv::waitKey(10)&0xff;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    return;
  }
    if(key==27||key==13)
            ros::shutdown();
    else if(key=='s')
            cv::imwrite( "output.jpg", frame );
}
static void ch(int, void*)
{
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "node2");
  ros::NodeHandle n;
  image_transport::ImageTransport it(n);
  image_transport::Subscriber sub = it.subscribe("cam1", 1, imageCallback);
  cv::namedWindow("n2");
  cv::startWindowThread();
   cv::createTrackbar( "R min","n2", &Rmin,255, ch );
   cv::createTrackbar( "R max","n2", &Rmax,255, ch );
   cv::createTrackbar( "G min","n2", &Gmin,255, ch );
   cv::createTrackbar( "G max","n2", &Gmax,255, ch );
   cv::createTrackbar( "B min","n2", &Bmin,255, ch );
   cv::createTrackbar( "B max","n2", &Bmax,255, ch );
  ch(0,0);
  ros::spin();
  cv::destroyAllWindows();
  return 0;
}
