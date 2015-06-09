#ifndef COMMONFUNCTIONS_H_
#define COMMONFUNCTIONS_H_

#include <opencv2/opencv.hpp>

void convertHSV(const cv::Mat& image);
cv::Mat indexSegments(const cv::Mat& image);
bool isLess(const cv::Vec3f& v1, const cv::Vec3f& v2);
cv::Mat selectColor(const cv::Mat& image, const cv::Vec3b& minValues, const cv::Vec3b& maxValues);

#endif /* COMMONFUNCTIONS_H_ */
