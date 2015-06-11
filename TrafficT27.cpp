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
	image = morphologyOpen(image, params.morphologyIter);
	image = morphologyClose(image, params.morphologyIter);

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
	cout << "Recognition starting...\n";
	Mat image = inputImage.clone();
	convertHSV(image);

	vector<Object> backObj, circleObj, girlObj, stickObj;

	cout << "Finding yellow backgrounds...\n";
	findElement(image, backObj, BACKGROUND_PARAMS);

	cout << "Finding red circles...\n";
	//findElement(image, circleObj, CIRCLE_PARAMS);

	cout << "Finding black girls...\n";
	//findElement(image, girlObj, GIRL_PARAMS);

	cout << "Finding white elements...\n";
	//findElement(image, stickObj, STICK_PARAMS);

	cout << "Merging results...\n";
	// TODO: merge objects

	cout << "Drawing results...\n";
	Mat outputImage = selectColor(image, BACKGROUND_PARAMS.minHSV, BACKGROUND_PARAMS.maxHSV);
	for(auto it = backObj.begin(); it != backObj.end(); ++it)
		(*it).drawOnImage(outputImage);

	return outputImage;
}
