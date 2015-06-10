/*
 * Segmentation.h
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <opencv2/opencv.hpp>

#include "Common.h"

// Label - type used to index segments
typedef cv::Vec3b Label;

const Label BACKGROUND = BLACK_VEC;
const Label FIRST_LABEL = Label(1, 0, 0);
const Label LAST_LABEL = WHITE_VEC;

// generate next Label
Label nextLabel(const Label& lab);

// get label from pixel
Label getLabel(const cv::Vec3b& vec);

// set label to pixel
void setLabel(cv::Vec3b& vec, const Label& lab);

// table (LUT) used to merge segments
class LabelTable
{
public:
	void setLabel(const cv::Vec3b& vec, const Label& lab);
	Label getLabel(const cv::Vec3b& vec);
private:
	std::map<cv::Vec3b, Label, Comparator<cv::Vec3b> > table_;
};

cv::Mat indexSegments(const cv::Mat& image);

#endif /* SEGMENTATION_H_ */
