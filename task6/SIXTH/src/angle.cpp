
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
#include <sstream>
using namespace cv;
using namespace std;

int Hmin,Hmax,Smin,Smax,Vmin,Vmax;
static void ch(int, void*)
{
}
int main(int argc, char ** argv )
{
   Mat src, HSV, dst, mask;
   namedWindow( "n3", WINDOW_AUTOSIZE );
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
    if(!src.empty()) 
    {
        GaussianBlur( src, dst, Size( 9, 9 ), 0, 0 );
        cvtColor(dst, HSV, cv::COLOR_BGR2HSV);
        Scalar minHSV = cv::Scalar(Hmin,Smin,Vmin);
        Scalar maxHSV = cv::Scalar(Hmax,Smax,Vmax);
        inRange(HSV, minHSV, maxHSV, mask);
	Canny( mask, mask, 75, 150, 3 );
	vector<Vec4i> lines; 
        HoughLinesP(mask, lines, 1, CV_PI/180, 40, 10,30 );
	if(lines.size()>2)
	{
		Vec4i l = lines[0];
		int x1=l[0],x2=l[2],y1=l[1],y2=l[3],x=0,y=0,ln=lines.size();
		double th=(x1==x2)?90:atan(1.0*(y2-y1)/(x2-x1))*180/CV_PI;
		double m=th,M=th;
		for( size_t i = 0; i < ln; i++ )
	    	{
			Vec4i l = lines[i];
			line( src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
			x1=l[0];x2=l[2];y1=l[1];y2=l[3];
			x+=x1+x2;
		    	y+=y1+y2;
			double th=(x1==x2)?90:atan(1.0*(y2-y1)/(x2-x1))*180/CV_PI;
			if (th>M)M=th;
			if(th<m)m=th;
	    	}
		x=(x/ln/2);
		y=(y/ln/2);
		if((M-m)>5)
		{
	 		stringstream ss;
			ss<<"angle = "<<(M-m);
			putText(src, ss.str(),Point(x,y+5),FONT_HERSHEY_PLAIN,2,Scalar(255,255,0),2,LINE_AA);
		}else
			putText(src,"unable to resolve",Point(x,y+5),FONT_HERSHEY_PLAIN,2,Scalar(0,0,255),2,LINE_AA);
	}
        imshow( "n3", src);
        if((waitKey(50)&0xff)==13)break;
    }
    }
destroyAllWindows();
return 0;
}
