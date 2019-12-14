#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node1");
  ros::NodeHandle n;
  image_transport::ImageTransport it(n);
  image_transport::Publisher pub1 = it.advertise("cam1", 1);
image_transport::Publisher pub2 = it.advertise("cam2", 1);
  ros::Rate loop_rate(15);

  cv::VideoCapture cap(0);
  cv::namedWindow("n1");
  cv::startWindowThread();
  if(!cap.isOpened())
    return -1;

  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  while (n.ok()) {
    cap >> frame;
    if(!frame.empty()) {
        cv::imshow("n1", frame);
        msg= cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub1.publish(msg);
	pub2.publish(msg);
        cv::waitKey(1);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  cv::destroyAllWindows();
  return 0;
}
