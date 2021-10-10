#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;

//Basic functions-------------------------------
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	//variable for images
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;
	//convert img to Gray
	cvtColor(img, imgGray,COLOR_BGR2GRAY);
	//blur img
	GaussianBlur(img, imgBlur,Size(7,7),5,0);
	//use blur before canny edge detector
	//more edges if decarease numbers
	Canny(imgBlur, imgCanny, 25,75);
	//dialate images
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernal);
	//erode image/ clean up
	erode(imgDilate, imgErode, kernal);
	//display images
	imshow("blur_img", imgBlur);
	imshow("Image", imgGray);
	imshow("canny", imgCanny);
	imshow("imgDilate", imgDilate);
	imshow("imgErode", imgErode);
	waitKey(0);

}