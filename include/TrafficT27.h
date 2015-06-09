#ifndef TRAFFICT27_H_
#define TRAFFICT27_H_

#include <opencv2/opencv.hpp>

cv::Mat findRedCircle(const cv::Mat& image);
cv::Mat findTrafficT27(const cv::Mat& image);

#endif /* TRAFFICT27_H_ */
