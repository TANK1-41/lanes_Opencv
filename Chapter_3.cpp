#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;

void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize,imgCrop;

	//cout << img.size() << endl;//check the size of an image
	//
	//resize an image
	//resize(img, imgResize,Size(640,480));
	// 
	//scale an image down
	resize(img, imgResize, Size(),0.5, 0.5);//scales image by 1/2

	//crop an image
	//rect is a data type to hold a rectangle
	Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	//display image
	imshow("Image", img);
	imshow("resize", imgResize);
	imshow("crop", imgCrop);
	waitKey(0);
	
}
