#include "TrafficT27.h"
#include "Common.h"
#include "Consts.h"
#include "Segmentation.h"
#include "Object.h"

using namespace cv;
using namespace std;

Mat findRedCircle(const Mat& inputImage)
{
	Mat image = selectColor(inputImage, CIRCLE_HSV_MIN_VALUE, CIRCLE_HSV_MAX_VALUE);
	// TODO remove!!!
	cv::morphologyEx(image, image, MORPH_OPEN, cv::Mat(), Point(-1, -1), 3);
	cv::morphologyEx(image, image, MORPH_CLOSE, cv::Mat(), Point(-1, -1), 3);
	//image = indexSegments(image);

	Mat segImage = indexSegments(image);
	namedWindow("Segments", WINDOW_NORMAL);
	imshow("Segments", segImage);
	cout << Object::generateObjects(segImage).size() << endl;

	return image;
}

Mat findTrafficT27(const Mat& inputImage)
{
	Mat image = inputImage.clone();
	convertHSV(image);
	Mat redCircleImage = findRedCircle(image);
	return redCircleImage;
}
