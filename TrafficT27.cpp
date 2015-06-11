#include "TrafficT27.h"
#include "Common.h"
#include "Consts.h"
#include "Segmentation.h"
#include "Object.h"
#include "Parameters.h"

using namespace cv;
using namespace std;

void findElement(const cv::Mat& inputImage, std::vector<Object>& objects, const Parameters& params)
{
	Mat image = selectColor(inputImage, params.minHSV, params.maxHSV);
	// TODO remove!!!
	cv::morphologyEx(image, image, MORPH_OPEN, cv::Mat(), Point(-1, -1), 3);
	cv::morphologyEx(image, image, MORPH_CLOSE, cv::Mat(), Point(-1, -1), 3);

	Mat segImage = indexSegments(image);
	Object::generateObjects(segImage, objects, params.minSegmentSize, params.maxSegmentSize);
}

Mat findTrafficT27(const Mat& inputImage)
{
	Mat image = inputImage.clone();
	convertHSV(image);

	vector<Object> backObj, circleObj, girlObj, stickObj;

	Parameters backParams(
			BACKGROUND_HSV_MIN_VALUE, BACKGROUND_HSV_MAX_VALUE,
			BACKGROUND_MIN_SEGMENT_SIZE, BACKGROUND_MAX_SEGMENT_SIZE);

	Parameters circleParams(
			CIRCLE_HSV_MIN_VALUE, CIRCLE_HSV_MAX_VALUE,
			CIRCLE_MIN_SEGMENT_SIZE, CIRCLE_MAX_SEGMENT_SIZE);

	Parameters girlParams(
			GIRL_HSV_MIN_VALUE, GIRL_HSV_MAX_VALUE,
			GIRL_MIN_SEGMENT_SIZE, GIRL_MAX_SEGMENT_SIZE);

	Parameters stickParams(
			STICK_HSV_MIN_VALUE, STICK_HSV_MAX_VALUE,
			STICK_MIN_SEGMENT_SIZE, STICK_MAX_SEGMENT_SIZE);

	//findElement(image, backObj, backParams);
	findElement(image, circleObj, circleParams);
	//findElement(image, girlObj, girlParams);
	//findElement(image, stickObj, stickParams);

	// TODO: merge objects

	return selectColor(image, CIRCLE_HSV_MIN_VALUE, CIRCLE_HSV_MAX_VALUE);
}
