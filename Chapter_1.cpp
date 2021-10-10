#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
using namespace std;
using namespace cv;

//importanting images
/*
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	imshow("Image", img);
	waitKey(0);

}
*/


//importanting videos
/*
void main() {
	string path = "Resources/test_video.mp4";
	VideoCapture  cap(path);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(5);
	}
}*/

//importing webcam
void main() {
	
	//camera id can be 0,1,2,3 ect
	VideoCapture  cap(0);
	//opencv variable type used to store each frame
	Mat img;
	//show and update each frame
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}
