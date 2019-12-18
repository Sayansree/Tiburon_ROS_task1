
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int Hmin,Hmax,Smin,Smax,Vmin,Vmax;
static void ch(int, void*)
{
}
int main(int argc, char ** argv )
{
   Mat src, HSV, dst, mask;
   namedWindow( "threshold", WINDOW_AUTOSIZE );
   //createTrackbar( "H min","n3", &Hmin,180, ch );
   //createTrackbar( "H max","n3", &Hmax,180, ch );
   //createTrackbar( "S min","n3", &Smin,255, ch );
   //createTrackbar( "S max","n3", &Smax,255, ch );
  //createTrackbar( "V min","n3", &Vmin,255, ch );
   //createTrackbar( "V max","n3", &Vmax,255, ch );
   //ch(0,0);
   Hmin=20;Smin=80;Vmin=130;
   Hmax=39;Smax=255;Vmax=255;
   VideoCapture cap("robosub_path-1.mp4");
while(cap.isOpened())
    {
    cap >> src;
    if(!src.empty()) {
        GaussianBlur( src, dst, Size( 9, 9 ), 0, 0 );
        cvtColor(dst, HSV, cv::COLOR_BGR2HSV);
        Scalar minHSV = cv::Scalar(Hmin,Smin,Vmin);
        Scalar maxHSV = cv::Scalar(Hmax,Smax,Vmax);
        inRange(HSV, minHSV, maxHSV, mask);
        imshow( "threshold", mask);
        if((waitKey(50)&0xff)==13)break;
    }
    }
destroyAllWindows();
return 0;
}
