#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;

//warp images

//the with and hight of the dst image
float w = 250, h = 350;


void main() {
	string path = "Resources/cards.jpg";
	Mat img = imread(path);
	Mat imgResize, matrix, imgWarp;
	//defines that thier will be four points with src[4]
	//point2f shows it will be foating points
	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	//desination points
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	
	//warp image
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	//create cirlces around src points
	for (int i = 0; i < 4; i++) {
		circle(img, Point(src[i]), 10, Scalar(255, 0, 0), 1);
	}


	//display images
	imshow("Image", img);
	imshow("warpedimg", imgWarp);
	waitKey(0);

}
