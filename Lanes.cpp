#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;


/// <summary>
/// Identifying color in images
/// </summary>


Mat imgHSV, mask;
int hmin = 12, smin = 66, vmin = 213;
int hmax = 22, smax = 167, vmax = 255;


void getContours(Mat imgDialation, Mat img) {


	vector<vector<Point>> contours;
	vector<Vec4i> hieracrchy;

	findContours(imgDialation, contours, hieracrchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//draw contors
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0; i < contours.size(); i++) {
		//checks the area of each contour
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		//delets any that are too small
		if (area > 50) {
			float peri = arcLength(contours[i], true);//finds the bounding box around objects
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//amount of curves or corners in each shape
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//if -1 insted of i as seen above it will draw all of them
		}
	}
}



void main() {
	//string path = "Resources/road.jfif";
	//Mat img = imread(path);
	//Mat imgWhite = imread(path);
	Mat imgDilation, WimgDilation;

	//camera id can be 0,1,2,3 ect
	VideoCapture  cap(0);
	//opencv variable type used to store each frame
	Mat img;

	//convert img to HSV
	
	//cvtColor(img, imgHSV, COLOR_BGR2HSV);
	//track bar to find right max and min for color
	// 
	//creates window for track bar
	/*
	namedWindow("Trackbars", (640, 200));
	//Crate the trackbar
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	*/
	while (true) {
		cap.read(img);
		
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		//range of colors to be detected
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		//checks for color range
		inRange(imgHSV, lower, upper, mask);
		Mat kernal = getStructuringElement(MORPH_RECT, Size(2, 2));
		dilate(mask, imgDilation, kernal);
		getContours(imgDilation,img);
		
		//display image with overlay
		imshow("Image", imgDilation);
		imshow("imgage", img);
		
		/*
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		Mat kernal = getStructuringElement(MORPH_RECT, Size(2, 2));
		dilate(mask, imgDilation, kernal);
		getContours(imgDilation, img);
		imshow("Image", imgDilation);
		imshow("imgage", img);*/
		waitKey(1);
	}
}
