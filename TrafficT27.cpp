#include "TrafficT27.h"
#include "Common.h"
#include "Consts.h"
#include "Segmentation.h"
#include "Object.h"
#include "Parameters.h"

using namespace cv;
using namespace std;

void findElement(const cv::Mat& inputImage, std::list<Object>& objects, const Parameters& params)
{
	cout << "  Selecting color...\n";
	Mat image = selectColor(inputImage, params.minHSV, params.maxHSV);

	cout << "  Morphology open...\n";
	image = morphologyOpen(image, params.morphologyOpenIter);

	cout << "  Morphology close...\n";
	image = morphologyClose(image, params.morphologyCloseIter);

	cout << "  Segments finding...\n";
	Mat segImage = indexSegments(image);

	cout << "  Feature extraction...\n";
	Object::generateObjects(segImage, objects, params.minSegmentSize, params.maxSegmentSize);
	//for(auto it = objects.begin(); it != objects.end(); ++it)
		//cout << (*it) << endl;

	cout << "  Objects filtering...\n";
	filterObjects(objects, params.shapeParams);
	for(auto it = objects.begin(); it != objects.end(); ++it)
		cout << (*it) << endl;
}

void filterObjects(list<Object>& objects, const ShapeParameters& params) {
	double M1, M2, M3, M7, W3;
	auto it = objects.begin();
	auto nextIt = ++(objects.begin());
	auto endIt = objects.end();

	while(it != endIt) {
		M1 = (*it).getM1();
		M2 = (*it).getM2();
		M7 = (*it).getM7();
		W3 = (*it).getW3();
		if(M1 < params.minM1 || M1 > params.maxM1 ||
				M2 < params.minM2 || M2 > params.maxM2 ||
				M7 < params.minM7 || M7 > params.maxM7 ||
				W3 < params.minW3 || W3 > params.maxW3) {
			objects.erase(it);
		}
		it = nextIt;
		++nextIt;
	}
}

void mergeAllObjects(list<Object>& back, list<Object>& circle,
		list<Object>& girl, list<Object>& stick,
		list<Object>& resBack, list<Object>& resCircle,
		list<Object>& resGirl, list<Object>& resStick) {

	for(auto b = back.begin(); b != back.end(); ++b) {
		list<Object>::const_iterator ci, gi, si;
		bool isCircle = false, isStick = false, isGirl = false;
		for(auto s = stick.begin(); s != stick.end(); ++s)
			if(canMergeObjects((*s), (*b), BACKGROUND_STICK_REL)) {
				isStick = true;
				si = s;
				break;
			}
		for(auto c = circle.begin(); c != circle.end(); ++c)
			if(canMergeObjects((*c), (*b), BACKGROUND_CIRCLE_REL)) {
				isCircle = true;
				ci = c;
				break;
			}
		for(auto g = girl.begin(); g != girl.end(); ++g)
			if(canMergeObjects((*g), (*b), BACKGROUND_GIRL_REL)) {
				isGirl = true;
				gi = g;
				break;
			}
		if(isStick && isCircle && isGirl) {
			resBack.push_back(*b);
			resCircle.push_back(*ci);
			resGirl.push_back(*gi);
			resStick.push_back(*si);
		}
	}
}

bool canMergeObjects(const Object& o1, const Object& o2, const RelationParameters& params) {
	double size = ((double)o1.getSize() / (double)o2.getSize());
	Point center = o1.getCenter();
	Point max = o2.getMaxPoint(), min = o2.getMinPoint();
	if(size < params.minSizeRelation || size > params.maxSizeRelation ||
			center.x < min.x || center.x > max.x ||
			center.y < min.y || center.y > max.y)
		return false;
	return true;
}

Mat findTrafficT27(const Mat& inputImage)
{
	cout << "Recognition starting...\n";
	Mat image = inputImage.clone();
	convertHSV(image);
	//image = sharpenFilter(image, 1);

	list<Object> backObj, circleObj, girlObj, stickObj;

	cout << "Finding yellow backgrounds...\n";
	findElement(image.clone(), backObj, BACKGROUND_PARAMS);

	cout << "Finding red circles...\n";
	findElement(image.clone(), circleObj, CIRCLE_PARAMS);

	cout << "Finding black girls...\n";
	findElement(image.clone(), girlObj, GIRL_PARAMS);

	cout << "Finding white elements...\n";
	findElement(image.clone(), stickObj, STICK_PARAMS);

	cout << "Merging results...\n";
	list<Object> resBack, resCircle, resGirl, resStrick;
	mergeAllObjects(backObj, circleObj, girlObj, stickObj,
			resBack, resCircle, resGirl, resStrick);

	cout << "Drawing result...\n";
	Mat outputImage = inputImage.clone();

	// draw all objects
	for(auto it = circleObj.begin(); it != circleObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 0, 255));
	for(auto it = girlObj.begin(); it != girlObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 255, 255));
	for(auto it = stickObj.begin(); it != stickObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 0));
	for(auto it = backObj.begin(); it != backObj.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(0, 255, 0));

	// draw choosen objects
	for(auto it = resCircle.begin(); it != resCircle.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 255));
	for(auto it = resGirl.begin(); it != resGirl.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 255));
	for(auto it = resStrick.begin(); it != resStrick.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 255));
	for(auto it = resBack.begin(); it != resBack.end(); ++it)
		(*it).drawOnImage(outputImage, Scalar(255, 0, 255));

	cout << "Recognition finished.\n";
	return outputImage;
}
