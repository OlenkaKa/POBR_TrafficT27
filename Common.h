#ifndef COMMON_H_
#define COMMON_H_

#include <opencv2/opencv.hpp>

const cv::Vec3b BLACK_VEC(0, 0, 0);
const cv::Vec3b WHITE_VEC(255, 255, 255);

template<typename T>
bool isLess(const T& v1, const T& v2) {
	if(v1[0] < v2[0])
		return true;
	if(v1[0] > v2[0])
		return false;
	if(v1[1] < v2[1])
		return true;
	if(v1[1] > v2[1])
		return false;
	if(v1[2] < v2[2])
		return true;
	return false;
}

void convertHSV(const cv::Mat& image);
cv::Mat selectColor(const cv::Mat& image, const cv::Vec3b& minValues, const cv::Vec3b& maxValues);

cv::Mat dilate(const cv::Mat& image, int iterations);
cv::Mat erode(const cv::Mat& image, int iterations);
cv::Mat morphologyClose(const cv::Mat& image, int iterations);
cv::Mat morphologyOpen(const cv::Mat& image, int iterations);

cv::Mat sharpenFilter(const cv::Mat& image, int iterations);
cv::Mat medianFilter(const cv::Mat& image, int iterations);

template<class T>
struct Comparator
{
	bool operator() (T a, T b) {
		return isLess<T>(a, b);
	}
};

#endif /* COMMON_H_ */
