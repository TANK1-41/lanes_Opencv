#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>

using namespace std;
using namespace cv;


Mat rotate(Mat img, double angle)   //rotate function returning mat object with parametres imagefile and angle    
{
	Mat dst;      //Mat object for output image file
	Point2f pt(img.cols / 2., img.rows / 2.);          //point from where to rotate    
	Mat r = getRotationMatrix2D(pt, angle, 1.0);      //Mat object for storing after rotation
	warpAffine(img, dst, r, Size(img.cols, img.rows));  ///applie an affine transforation to image.
	return dst;         //returning Mat object for output image file
}

void main() {

	//camera id can be 0,1,2,3 ect
	VideoCapture  cap(0);
	
	//opencv variable type used to store each frame
	Mat img, imgGray, imgG, imgCanny, imgInterest, imgHougth;
	//img = imread("Resources/road.jfif");
	//show and update each frame
	while (true)
	{
		//read the frame
		cap.read(img);

		//rodate image
		img = rotate(img, 180);
		//convert the image to gray
		cvtColor(img, imgGray, COLOR_BGR2GRAY);

		//gaussian filter
		GaussianBlur(imgGray, imgG, Size(9, 9), 0, 0);
		//imshow("imgG", imgG);

		//canny edge detection 
		int minVal = 60;
		int maxVal = 150;

		// Define edge detection image, do edge detection
		Canny(imgG, imgCanny, minVal, maxVal);
		//imshow("imgCanny", imgCanny);
		
		//--------------------------Cred to https://github.com/StevieG47/Lane-Detection/blob/master/README.md ---------------//
		//Area of interset mask
		Mat mask(img.size().height, img.size().width, CV_8UC1, Scalar(0));

		Point p1 = Point(0, img.size().height);
		Point p2 = Point(455, 320);
		Point p3 = Point(505, 320);
		Point p4 = Point(img.size().width, img.size().height);

		// create vector from array with points we just defined
		Point vertices1[] = { p1,p2,p3,p4 };
		vector<Point> vertices(vertices1, vertices1 + sizeof(vertices1) / sizeof(Point));

		// Create vector of vectors, add the vertices we defined above
		// (you could add multiple other similar contours to this vector)
		vector<vector<Point> > verticesToFill;
		verticesToFill.push_back(vertices);

		// Fill in the vertices on the blank image, showing what the mask is
		fillPoly(mask, verticesToFill, Scalar(255, 255, 255));

		// Show the mask
		imshow("Mask", mask);

		//applying the mask
		Mat maskedIm = imgCanny.clone();
		bitwise_and(imgCanny, mask, maskedIm);

		// Show masked image
		imshow("Masked Image", maskedIm);

		//create hough lines
		float rho = 2;
		float pi = 3.14159265358979323846;
		float theta = pi / 180;
		float threshold = 45;
		int minLineLength = 40;
		int maxLineGap = 100;
		vector<Vec4i> lines; // A Vec4i is a type holding 4 integers
		HoughLinesP(maskedIm, lines, rho, theta, threshold, minLineLength, maxLineGap);

		if (!lines.empty() && lines.size() > 2) {

			// Initialize lines image
			Mat allLinesIm(img.size().height, img.size().width, CV_8UC3, Scalar(0, 0, 0)); // CV_8UC3 to make it a 3 channel)

			// Loop through lines
			// std::size_t can store the maximum size of a theoretically possible object of any type
			for (size_t i = 0; i != lines.size(); ++i) {

				// Draw line onto image
				line(img, Point(lines[i][0], lines[i][1]),
					Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
				line(allLinesIm, Point(lines[i][0], lines[i][1]),
					Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
			}
			imshow("Hough Lines", allLinesIm);
		}

		//---------------------------------end of cred to https://github.com/StevieG47/Lane-Detection/blob/master/README.md --------------//
		imshow("Image", img);
		waitKey(1);
	}
}
