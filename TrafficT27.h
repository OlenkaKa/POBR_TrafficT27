#ifndef TRAFFICT27_H_
#define TRAFFICT27_H_

#include <opencv2/opencv.hpp>

#include "Object.h"
#include "Parameters.h"

void findElement(const cv::Mat& image, std::list<Object>& objects, const Parameters& params);
void filterObjects(std::list<Object>& objects, const ShapeParameters& params);
void mergeAllObjects(std::list<Object>& back, std::list<Object>& circle,
		std::list<Object>& girl, std::list<Object>& stick, std::list<Object>& result);
bool canMergeObjects(const Object& o1, const Object& o2, const RelationParameters& params);

cv::Mat findTrafficT27(const cv::Mat& image);

#endif /* TRAFFICT27_H_ */
