#include "TrafficT27.h"
#include "CommonFunctions.h"

using namespace cv;

Mat findTrafficT27(const Mat& inputImage)
{
	Mat image = inputImage.clone();
	convertHSV(image);
	image = selectColor(image, Vec3b(0,0,0), Vec3b(2,255,255));
	return image;
}
