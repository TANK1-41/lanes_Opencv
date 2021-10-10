#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;



Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

void getContours(Mat imgDialation,Mat img){

	
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
		if (area > 1000) {
			float peri = arcLength(contours[i],true);//finds the bounding box around objects
			approxPolyDP(contours[i],conPoly[i],0.02*peri,true);//amount of curves or corners in each shape
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//if -1 insted of i as seen above it will draw all of them
		}
	}
}



void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);
	

	
	//--------Preprocessing----------------
	//covert image to gary
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//blur img
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	//use blur before canny edge detector
	//more edges if decarease numbers
	Canny(imgBlur, imgCanny, 15, 50);
	//dialate images
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernal);
	

	//call for getContors
	getContours(imgDilate,img);
	//dispaly test images
	imshow("Image", img);
	/*
	imshow("image gray", imgGray);
	imshow("image blur", imgBlur);
	imshow("image Canny", imgCanny);
	imshow("image Dilate", imgDilate);
	*/
	waitKey(0);
}