#ifndef TRAFFICT27_H_
#define TRAFFICT27_H_

#include <opencv2/opencv.hpp>

#include "Object.h"
#include "Parameters.h"

void findElement(const cv::Mat& image, std::vector<Object>& objects, const Parameters& params);
void filterObjects(std::vector<Object>& objects, const ShapeParameters& params);
void mergeAllObjects(std::vector<Object>& back, std::vector<Object>& circle,
		std::vector<Object>& girl, std::vector<Object>& stick, std::vector<Object>& result);
bool canMergeObjects(const Object& o1, const Object& o2, const RelationParameters& params);

cv::Mat findTrafficT27(const cv::Mat& image);

#endif /* TRAFFICT27_H_ */
