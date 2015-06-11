#ifndef TRAFFICT27_H_
#define TRAFFICT27_H_

#include <opencv2/opencv.hpp>

#include "Object.h"
#include "Parameters.h"

void findElement(const cv::Mat& image, std::vector<Object>& objects, const Parameters& params);
void filterObjects(std::vector<Object>& objects, const ShapeParameters& params);

cv::Mat findTrafficT27(const cv::Mat& image);

#endif /* TRAFFICT27_H_ */
