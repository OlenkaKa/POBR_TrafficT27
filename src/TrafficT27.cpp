#include "TrafficT27.h"
#include "CommonFunctions.h"
#include "Consts.h"

using namespace cv;

Mat findRedCircle(const Mat& inputImage)
{
	Mat image = selectColor(inputImage, CIRCLE_HSV_MIN_VALUE, CIRCLE_HSV_MAX_VALUE);
	// TODO remove!!!
	cv::morphologyEx(image, image, MORPH_OPEN, cv::Mat(), Point(-1, -1), 3);
	cv::morphologyEx(image, image, MORPH_CLOSE, cv::Mat(), Point(-1, -1), 3);
	//image = indexSegments(image);

	namedWindow("segments", WINDOW_NORMAL);
	imshow("segments", indexSegments(image));

	return image;
}

Mat findTrafficT27(const Mat& inputImage)
{
	Mat image = inputImage.clone();
	convertHSV(image);
	Mat redCircleImage = findRedCircle(image);
	return redCircleImage;
}
