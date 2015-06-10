#ifndef COMMON_H_
#define COMMON_H_

#include <opencv2/opencv.hpp>

const cv::Vec3b BLACK_VEC(0, 0, 0);
const cv::Vec3b WHITE_VEC(255, 255, 255);

void convertHSV(const cv::Mat& image);
bool isLess(const cv::Vec3b& v1, const cv::Vec3b& v2);

cv::Mat selectColor(const cv::Mat& image, const cv::Vec3b& minValues, const cv::Vec3b& maxValues);

//cv::Mat dilate(const cv::Mat& image, int iterations);
//cv::Mat erode(const cv::Mat& image, int iterations);

cv::Mat medianFilter(const cv::Mat& image, int iterations);

template<class T>
struct Comparator
{
	bool operator() (T a, T b) {
		return isLess(a, b);
	}
};

#endif /* COMMON_H_ */
