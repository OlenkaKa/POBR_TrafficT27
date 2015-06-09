#ifndef COMMONFUNCTIONS_H_
#define COMMONFUNCTIONS_H_

#include <opencv2/opencv.hpp>

void convertHSV(const cv::Mat& image);
cv::Mat selectColor(const cv::Mat& image, const cv::Vec3b& minValues, const cv::Vec3b& maxValues);

#endif /* COMMONFUNCTIONS_H_ */
