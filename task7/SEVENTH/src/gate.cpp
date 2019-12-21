
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

int Hmin,Hmax,Smin,Smax,Vmin,Vmax,k,s,d,tre;
static void ch(int, void*)
{
}
int main(int argc, char ** argv )
{
   Mat src, HSV, dst, dx ,dy,mask,gray,mask2;
   Mat element = getStructuringElement( MORPH_RECT,Size( 3,3 ),Point(1,1 ) );
   namedWindow( "BGR", WINDOW_AUTOSIZE );
   namedWindow( "HSV", WINDOW_AUTOSIZE );
   //createTrackbar( "H min","HSV", &Hmin,180, ch );
   //createTrackbar( "H max","HSV", &Hmax,180, ch );
   //createTrackbar( "S min","HSV", &Smin,255, ch );
   //createTrackbar( "S max","HSV", &Smax,255, ch );
   //createTrackbar( "V min","HSV", &Vmin,255, ch );
   //createTrackbar( "V max","HSV", &Vmax,255, ch );
	//createTrackbar( "thresh","ge", &k,200, ch );
	//createTrackbar( "min leng","ge", &s,100, ch );
	//createTrackbar( "min gap","ge", &d,255, ch );
	//createTrackbar( "th for gate","ge", &tre,50, ch );
	
   	ch(0,0);
	setTrackbarPos("lo", "HSV", 7);
	setTrackbarPos("high", "HSV", 10);
  	 Hmin=0;Smin=50;Vmin=165;
  	Hmax=30;Smax=85;Vmax=210;
	k=90;s=86;d=56; tre =18;
	
   	VideoCapture cap("/home/sayansree/catkin_ws/src/ross/src/gate.avi");
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
  	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
	VideoWriter video("output.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
while(cap.isOpened())
    {
    cap >> src;
    if(!src.empty()) {
        GaussianBlur( src, dst, Size( 9, 9 ), 0, 0 );
	cvtColor(dst, gray, COLOR_BGR2GRAY);
        cvtColor(dst, HSV, COLOR_BGR2HSV);

        Scalar minHSV = cv::Scalar(Hmin,Smin,Vmin);
        Scalar maxHSV = cv::Scalar(Hmax,Smax,Vmax);
        inRange(HSV, minHSV, maxHSV, mask);
	mask(Range(0,150),Range(0,mask.cols))=0; 
	erode(mask,mask,element);
	Sobel(mask, dy,  CV_16S, 0,1, 3,1, 0, BORDER_DEFAULT);
        convertScaleAbs(dy, mask2);	     	
	vector<Vec4i> linesy,lines; 
        HoughLinesP(mask2, lines, 1, CV_PI/180, k, s,d );
	
		for( size_t i = 0; i < lines.size(); i++ )
	    	{
			
			Vec4i l = lines[i];
			int x1=l[0],x2=l[2],y1=l[1],y2=l[3];
			double th=(x1==x2)?90:atan(1.0*(y2-y1)/(x2-x1))*180/CV_PI;
			if(abs(th)<7)
			{
				line( HSV, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
				linesy.push_back(l);
			}
			
	    	}
	Sobel(mask, dx,  CV_16S, 1,0, 3,1, 0, BORDER_DEFAULT);
        convertScaleAbs(dx, mask2);	     	
        HoughLinesP(mask2, lines, 1, CV_PI/180, k, s,d );
	int x=-1,y=-1,X=-1,Y=-1;
	
		for( size_t i = 0; i < lines.size(); i++ )
	    	{
			
			Vec4i l = lines[i];
			int x1=l[0],x2=l[2],y1=l[1],y2=l[3];
			double th=(x1==x2)?90:atan(1.0*(y2-y1)/(x2-x1))*180/CV_PI;
			if(abs(th)>83)
			{	int xx=(x1+x2)/2;
				line( HSV, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,255,0), 3, LINE_AA);
				for( size_t j = 0; j < linesy.size(); j++ )
	    			{
					
					l = linesy[j];
					int X1=l[0],X2=l[2],Y1=l[1],Y2=l[3];
					int yy= (Y1+Y2)/2;
					if((abs(xx-X1)<tre||abs(xx-X2)<tre)&&(abs(yy-min(y1,y2))<tre))
					{
						Y=max(Y,max(y1,y2));
						X=max(X,max(X1,X2));
						x=xx;y=yy;
						circle(HSV,Point(x,y),5,Scalar(0,255,255));
						circle(HSV,Point(x,Y),5,Scalar(0,255,255));
						circle(HSV,Point(X,y),5,Scalar(0,255,255));
					}
		    		}
			}
			
	    	}
	if(Y>0){
		line( src, Point(x,y), Point(x,Y), Scalar(255,255,0),3, LINE_AA);
		line( src, Point(x,y), Point(X,y), Scalar(255,255,0), 3, LINE_AA);
		line( src, Point(X,y), Point(X,Y), Scalar(255,255,0), 3, LINE_AA);
		line( src, Point(x,Y), Point(X,Y), Scalar(255,255,0), 3, LINE_AA);
		X=max((int)(x+(Y-y)*0.866),(x+X)/2);//b/2h ratio 0.866
		Y=(Y+y)/2;		
		circle(src,Point(X,Y),5,Scalar(255,0,255),3);
		}
	
        imshow( "HSV", HSV);
	imshow( "BGR",src);    
	video.write(HSV);	
        if((waitKey(10)&0xff)==13)break;
    }
    }
cap.release();
video.release();
destroyAllWindows();
return 0;
}
