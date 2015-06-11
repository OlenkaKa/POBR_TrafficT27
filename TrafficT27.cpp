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
	cout << "  Selecting color...\n";
	Mat image = selectColor(inputImage, params.minHSV, params.maxHSV);

	cout << "  Morphology open...\n";
	image = morphologyOpen(image, params.morphologyIter);

	cout << "  Morphology close...\n";
	image = morphologyClose(image, params.morphologyIter);

	cout << "  Segments finding...\n";
	Mat segImage = indexSegments(image);

	cout << "  Feature extraction...\n";
	Object::generateObjects(segImage, objects, params.minSegmentSize, params.maxSegmentSize);
	for(auto it = objects.begin(); it != objects.end(); ++it)
		cout << (*it) << endl;

	cout << "  Objects filtering...\n";
	filterObjects(objects, params.shapeParams);
	for(auto it = objects.begin(); it != objects.end(); ++it)
		cout << (*it) << endl;
}

void filterObjects(vector<Object>& objects, const ShapeParameters& params) {
	double M1, M7, W3;
	auto it = objects.begin();
	auto nextIt = it;	++nextIt;
	auto endIt = objects.end();

	while(it != endIt) {
		M1 = (*it).getM1();
		M7 = (*it).getM7();
		W3 = (*it).getW3();
		if(M1 < params.minM1 || M1 > params.maxM1 ||
				M7 < params.minM7 || M7 > params.maxM7 ||
				W3 < params.minW3 || W3 > params.maxW3) {
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
	findElement(image.clone(), backObj, BACKGROUND_PARAMS);

	cout << "Finding red circles...\n";
	//findElement(image.clone(), circleObj, CIRCLE_PARAMS);

	cout << "Finding black girls...\n";
	//findElement(image.clone(), girlObj, GIRL_PARAMS);

	cout << "Finding white elements...\n";
	//findElement(image.clone(), stickObj, STICK_PARAMS);

	cout << "Merging results...\n";
	// TODO: merge objects

	cout << "Drawing result...\n";
	Mat outputImage = inputImage.clone();

	/*
	Mat outputImage = selectColor(image, BACKGROUND_PARAMS.minHSV, BACKGROUND_PARAMS.maxHSV);
	outputImage = morphologyOpen(outputImage, BACKGROUND_PARAMS.morphologyIter);
	outputImage = morphologyClose(outputImage, BACKGROUND_PARAMS.morphologyIter);
	*/
	/*
	Mat outputImage = selectColor(image, CIRCLE_PARAMS.minHSV, CIRCLE_PARAMS.maxHSV);
	outputImage = morphologyOpen(outputImage, CIRCLE_PARAMS.morphologyIter);
	outputImage = morphologyClose(outputImage, CIRCLE_PARAMS.morphologyIter);
	*/
	/*
	Mat outputImage = selectColor(image, GIRL_PARAMS.minHSV, GIRL_PARAMS.maxHSV);
	outputImage = morphologyOpen(outputImage, GIRL_PARAMS.morphologyIter);
	outputImage = morphologyClose(outputImage, GIRL_PARAMS.morphologyIter);
	*/
	/*
	Mat outputImage = selectColor(image, STICK_PARAMS.minHSV, STICK_PARAMS.maxHSV);
	outputImage = morphologyOpen(outputImage, STICK_PARAMS.morphologyIter);
	outputImage = morphologyClose(outputImage, STICK_PARAMS.morphologyIter);
	*/

	for(auto it = backObj.begin(); it != backObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 0));
	for(auto it = circleObj.begin(); it != circleObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 255, 0));
	for(auto it = girlObj.begin(); it != girlObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 0, 255));
	for(auto it = stickObj.begin(); it != stickObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 255, 255));

	cout << "Recognition finished.\n";
	return outputImage;
}
