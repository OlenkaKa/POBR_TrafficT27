#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "TrafficT27.h"

using namespace cv;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <Image_Path>\n", argv[0]);
		return -1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		printf("Could not open or find the image\n");
		return -1;
	}

	namedWindow("Input Image", WINDOW_NORMAL);
	imshow("Input Image", image);

	namedWindow("Output Image", WINDOW_NORMAL);
	imshow("Output Image", findTrafficT27(image));

	/*
	namedWindow("test", WINDOW_NORMAL);
	Mat test;
	cvtColor(image, test, CV_BGR2HSV);
	imshow("test", test);
	*/

	waitKey(0);
    return 0;
}
