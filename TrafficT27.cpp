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

	filterObjects(objects, params.shapeParams);
}

void filterObjects(vector<Object>& objects, const ShapeParameters& params) {
	double W3, M7;
	auto it = objects.begin();
	auto nextIt = it;	++nextIt;
	auto endIt = objects.end();

	while(it != endIt) {
		W3 = (*it).getW3();
		M7 = (*it).getM7();
		if(W3 < params.minW3 || W3 > params.maxW3 ||
				M7 < params.minM7 || M7 > params.maxM7) {
			objects.erase(it);
		}
		it = nextIt;
		++nextIt;
	}
}

Mat findTrafficT27(const Mat& inputImage)
{
	Mat image = inputImage.clone();
	convertHSV(image);

	vector<Object> backObj, circleObj, girlObj, stickObj;

	//findElement(image, backObj, BACKGROUND_PARAMS);
	//findElement(image, circleObj, CIRCLE_PARAMS);
	//findElement(image, girlObj, GIRL_PARAMS);
	//findElement(image, stickObj, STICK_PARAMS);

	// TODO: merge objects

	Mat outputImage = selectColor(image, CIRCLE_PARAMS.minHSV, CIRCLE_PARAMS.maxHSV);
	for(auto it = circleObj.begin(); it != circleObj.end(); ++it)
		(*it).drawOnImage(outputImage);

	return outputImage;
}
