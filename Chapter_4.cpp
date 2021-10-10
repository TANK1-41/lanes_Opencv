#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;

void main() {
	//blank image
	Mat img(512,512,CV_8UC3,Scalar(255,255,255));
	//create a circle
	//256 is the center point of the circle and 155 is the radius and 10 is the cirlce thickness(replace with FILL to fill circle
	circle(img, Point(256, 256), 155, Scalar(255, 0, 0),10);

	//createing a reactange
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 0), FILLED);
	

	//draw a line
	line(img, Point(130, 296), Point(382, 296), Scalar(0, 0, 0), 2);

	//put text 
	putText(img, "bacon", Point(137, 262), FONT_HERSHEY_COMPLEX, .75, Scalar(0, 240, 130), 2);
	imshow("Image", img);
	waitKey(0);

}
