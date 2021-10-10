#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;


/// <summary>
/// Identifying color in images
/// </summary>


Mat imgHSV,mask;
int hmin = 12, smin = 66, vmin = 213;
int hmax = 22, smax = 167, vmax = 255;


void main() {
	string path = "Resources/road.jfif";
	Mat img = imread(path);
	Mat imgDilation;
	//convert img to HSV
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
	//track bar to find right max and min for color
	// 
	//creates window for track bar
	namedWindow("Trackbars", (640, 200));
	//Crate the trackbar
	createTrackbar("Hue Min", "Trackbars", &hmin,179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	
	while(true){
		//range of colors to be detected
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		//checks for color range
		inRange(imgHSV, lower, upper, mask);
		//display images and trackbar
		imshow("Image", img);
		imshow("HSV", imgHSV);
		imshow("mask", mask);
		waitKey(1);
	}
}

