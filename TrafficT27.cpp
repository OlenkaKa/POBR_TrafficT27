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

void mergeAllObjects(vector<Object>& back, vector<Object>& circle,
		vector<Object>& girl, vector<Object>& stick, vector<Object>& result) {
	for(auto b = back.begin(); b != back.end(); ++b) {
		bool isCircle = false, isStick = false, isGirl = false;
		for(auto s = stick.begin(); s != stick.end(); ++s)
			if(canMergeObjects((*b), (*s), BACKGROUND_STICK_REL)) {
				isStick = true;
				break;
			}
		for(auto c = circle.begin(); c != circle.end(); ++c)
			if(canMergeObjects((*b), (*c), BACKGROUND_CIRCLE_REL)) {
				isCircle = true;
				break;
			}
		for(auto g = girl.begin(); g != girl.end(); ++g)
			if(canMergeObjects((*b), (*g), BACKGROUND_GIRL_REL)) {
				isGirl = true;
				break;
			}
		if(isStick && isCircle && isGirl)
			result.push_back(*b);
	}
}

bool canMergeObjects(const Object& o1, const Object& o2, const RelationParameters& params) {
	double size = o1.getSize() / o2.getSize();
	Point diff = (o1.getCenter() - o2.getCenter());
	if(size < params.minSizeRelation || size > params.maxSizeRelation)
		return false;
	return true;
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
	findElement(image.clone(), circleObj, CIRCLE_PARAMS);

	cout << "Finding black girls...\n";
	//findElement(image.clone(), girlObj, GIRL_PARAMS);

	cout << "Finding white elements...\n";
	//findElement(image.clone(), stickObj, STICK_PARAMS);

	cout << "Merging results...\n";
	vector<Object> result;
	//mergeAllObjects(backObj, circleObj, girlObj, stickObj, result);

	cout << "Drawing result...\n";
	Mat outputImage = inputImage.clone();
	for(auto it = backObj.begin(); it != backObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 255, 0));
	for(auto it = circleObj.begin(); it != circleObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 255, 0));

	cout << "Recognition finished.\n";
	return outputImage;
}
