// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

int HueLower = 158;
int	HueUpper = 179;
int Hue2Lower = 0;
int	Hue2Upper = 39;
int SatLow = 255;
int	SatHigh = 255;
int ValLow = 190;
int	ValHigh = 255;
int threshold1 = 255;
int threshold2 = 68;

int P1 = 0;
int P2 = 1600;

int main(int argc,char **argv){
	//Initializing Variables
	std::vector<cv::Vec4f>lines;
	std::vector<cv::Point> point;
	bool ret;
	int width, height;
	
	cv::Mat frame,hsv_frame,frame_detected;
	cv::Mat F_mask_1,F_mask_2,F_mask_added;
	cv::Mat B_mask,FG,BG,final_frame,bw;

	cv::namedWindow("Trackbars");
	cv::namedWindow("HoughParam");

	cv::VideoCapture vid("path1.mp4");


	width = (int)vid.get(cv::CAP_PROP_FRAME_WIDTH);
	height = (int)vid.get(cv::CAP_PROP_FRAME_HEIGHT);
	

	
	cv::createTrackbar("HueLower", "Trackbars", &HueLower, 179);
	cv::createTrackbar("HueUpper", "Trackbars", &HueUpper, 179);

	cv::createTrackbar("Hue2Lower", "Trackbars", &Hue2Lower, 179);
	cv::createTrackbar("Hue2Upper", "Trackbars", &Hue2Upper, 179);

	cv::createTrackbar("SatLow", "Trackbars", &SatLow, 255);
	cv::createTrackbar("SatHigh", "Trackbars", &SatHigh, 255);
	
	cv::createTrackbar("ValLow", "Trackbars", &ValLow, 255);
	cv::createTrackbar("ValHigh", "Trackbars",&ValHigh, 255);

	cv::createTrackbar("Threshold1", "Trackbars", &threshold1, 255);
	cv::createTrackbar("Threshold2", "Trackbars", &threshold2, 255);

	cv::createTrackbar("Threshold1", "Trackbars", &threshold1, 255);
	cv::createTrackbar("Threshold2", "Trackbars", &threshold2, 255);

	cv::resizeWindow("Trackbars", 480, 200);


	cv::createTrackbar("Length", "HoughParam", &P1, 4000);
	cv::createTrackbar("Gap", "HoughParam", &P2, 4000);
	
	
	
	while(1){
		ret  = vid.read(frame);
		if (ret == 0){
			vid.set(cv::CAP_PROP_POS_FRAMES, 0);
			ret = vid.read(frame);
			if (ret == 0){
				std::cout << "Failed Again! Exiting \n";
				return 1;
			}
			
		}
		frame_detected = frame.clone();
		

		cv::cvtColor(frame,hsv_frame,cv::COLOR_BGR2HSV);

		inRange(hsv_frame, cv::Scalar(HueLower, SatLow, ValLow), cv::Scalar(HueUpper, SatHigh, ValHigh), F_mask_1);
		inRange(hsv_frame, cv::Scalar(Hue2Lower, SatLow, ValLow), cv::Scalar(Hue2Upper, SatHigh, ValHigh), F_mask_2);
	
		cv::add(F_mask_1, F_mask_2, F_mask_added);

		cv::bitwise_and(frame, frame, FG, F_mask_added);
		cv::bitwise_not(F_mask_added,B_mask);

		cv::cvtColor(B_mask, BG, cv::COLOR_GRAY2BGR);
		cv::add(FG, BG, final_frame);
		
		cv::cvtColor(final_frame, bw, cv::COLOR_BGR2GRAY);
		cv::Canny(bw, bw, threshold1, threshold2);
		
		
		cv::HoughLinesP(bw, lines, 1, CV_PI/180, 30,P1,P2);

		for (size_t i = 0; i < lines.size(); i++){
			cv::Point pt1, pt2;
			pt1.x = lines[i][0];
			pt1.y = lines[i][1];
			pt2.x = lines[i][2];
			pt2.y = lines[i][3];
			
			line(frame_detected, pt1, pt2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
		}

		cv::imshow("Output", final_frame);
		cv::imshow("Detected", frame_detected);
		cv::imshow("Original", frame);
		cv::imshow("CannyTransform",bw);
		
		if (cv::waitKey(20) == 'q')
			break;
	}
	vid.release();
	cv::destroyAllWindows();
	return 0;
	
}



























































/*****************************************************************************
using namespace std;
using namespace cv;

//Global Variables for Trackbars
int HueLower = 0;
int	HueUpper = 52;
int Hue2Lower = 130;
int	Hue2Upper = 179;
int SatLow = 50;
int	SatHigh = 255;
int ValLow = 92;
int	ValHigh = 255;
int threshold1 = 255;
int threshold2 = 68;


int X1 = 392;
int X2 = 785;
int X3 = 1129;
int X4 = 0;
int Y1 = 343;
int Y2 = 343;
int Y3 = 646;
int Y4 = 646;
int P1 = 27;
int P2 = 218;


int main(int argc,char **argv)
{
	
	//Initializing Variables
	bool ret;
	int width, height;
	
	Mat frame,frame1,hsv_frame,F_mask_1,F_mask_2,F_mask_added,FG,B_mask,BG,final_frame,bw,mask2,mask3,mask4,maskTemp,inver;

	//Some Initialization
	namedWindow("Camera0");
	namedWindow("Trackbars");
	namedWindow("Canny");
	namedWindow("Mask_C");
	namedWindow("HoughParam");

	VideoCapture vid("vid1.mp4");
	//VideoCapture vid(0);
	width = (int)vid.get(CAP_PROP_FRAME_WIDTH);
	height = (int)vid.get(CAP_PROP_FRAME_HEIGHT);
	


	
	createTrackbar("HueLower", "Trackbars", &HueLower, 179);
	createTrackbar("HueUpper", "Trackbars", &HueUpper, 179);

	createTrackbar("Hue2Lower", "Trackbars", &Hue2Lower, 179);
	createTrackbar("Hue2Upper", "Trackbars", &Hue2Upper, 179);

	createTrackbar("SatLow", "Trackbars", &SatLow, 255);
	createTrackbar("SatHigh", "Trackbars", &SatHigh, 255);
	
	createTrackbar("ValLow", "Trackbars", &ValLow, 255);
	createTrackbar("ValHigh", "Trackbars",&ValHigh, 255);

	createTrackbar("Threshold1", "Trackbars", &threshold1, 255);
	createTrackbar("Threshold2", "Trackbars", &threshold2, 255);

	createTrackbar("Threshold1", "Trackbars", &threshold1, 255);
	createTrackbar("Threshold2", "Trackbars", &threshold2, 255);

	resizeWindow("Trackbars", 480, 200);


	createTrackbar("X1", "Mask_C", &X1, width);
	createTrackbar("Y1", "Mask_C", &Y1, height);

	createTrackbar("X2", "Mask_C", &X2, width);
	createTrackbar("Y2", "Mask_C", &Y2, height);

	createTrackbar("X3", "Mask_C", &X3, width);
	createTrackbar("Y3", "Mask_C", &Y3, height);

	createTrackbar("X4", "Mask_C", &X4, width);
	createTrackbar("Y4", "Mask_C", &Y4, height);

	resizeWindow("Mask_C", 480, 200);

	createTrackbar("Length", "HoughParam", &P1, 4000);
	createTrackbar("Gap", "HoughParam", &P2, 4000);

	

	

	
	
	
	while(1)
	{
		ret  = vid.read(frame);
		//resize(frame1, frame,cv::Size(1280,720), 0, 0, INTER_LINEAR);
		if (ret == 0)
		{
			cout << "Not Recieved Anything\n";
			vid.set(CAP_PROP_POS_FRAMES, 0);
			ret = vid.read(frame);
			if (ret == 0)
			{
				cout << "Failed Again! Exiting \n";
				return 1;
			}
			
		}

		Mat mask = cv::Mat::zeros(cv::Size(width, height), CV_8UC1); //Create Black Image
		vector<cv::Point> point;
		vector<Vec4f>lines;
		point.push_back(Point(X1, Y1));
		point.push_back(Point(X2, Y2));
		point.push_back(Point(X3, Y3));
		point.push_back(Point(X4, Y4));
		
		fillConvexPoly(mask, point , 255); //Fill it with white polygon
		cvtColor(mask,mask4,COLOR_GRAY2BGR);
		bitwise_and(frame, mask4, frame); 
		

		cvtColor(frame,hsv_frame,COLOR_BGR2HSV);

		inRange(hsv_frame, cv::Scalar(HueLower, SatLow, ValLow), cv::Scalar(HueUpper, SatHigh, ValHigh), F_mask_1);
		inRange(hsv_frame, cv::Scalar(Hue2Lower, SatLow, ValLow), cv::Scalar(Hue2Upper, SatHigh, ValHigh), F_mask_2);
	
		add(F_mask_1, F_mask_2, F_mask_added);

		bitwise_and(frame, frame, FG, F_mask_added);
		bitwise_not(F_mask_added,B_mask);

		cvtColor(B_mask, BG, COLOR_GRAY2BGR);
		add(FG, BG, final_frame);
		
		cvtColor(frame, bw, COLOR_BGR2GRAY);
		//GaussianBlur(frame, frame, cv::Size(5, 5), 150);
		Canny(bw, bw, threshold1, threshold2);
		
		fillConvexPoly(mask, point , 255); //Fill it with white polygon
		bitwise_and(bw, mask, mask2); 
		cvtColor(mask, mask3, COLOR_GRAY2BGR);
		bitwise_and(frame, mask3, mask3);
		
		//bitwise_not(mask2, inver);
		//HoughLinesP(mask2, lines, 1, CV_PI/180, 30,P1,P2);

		for (size_t i = 0; i < lines.size(); i++)
		{
			Point pt1, pt2;
			pt1.x = lines[i][0];
			pt1.y = lines[i][1];
			pt2.x = lines[i][2];
			pt2.y = lines[i][3];
			
			line(frame, pt1, pt2, Scalar(0, 255, 0), 3, LINE_AA);
		
		}
		
		

		
		
		//cout << frame.type();

		
		imshow("Camera0", frame);
		imshow("Final", final_frame);
		imshow("Canny", bw);
		imshow("Mask_Final", mask2);
		imshow("Mask", mask);
		//imshow("Mask_Final_Color", mask3);
		imshow("Mask_Final_Color_New", mask4);
		
		
		if (waitKey(20) == 'q')
			break;
	}
	vid.release();
	destroyAllWindows();
	return 0;
}*/

/***************************************************************************************************************************/
