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
typedef cv::Vec3s Label;
const int LABEL_TYPE = CV_16SC3;
const int LABEL_MAX_TYPE_VALUE = 10000;

const Label BACKGROUND = Label(0, 0, 0);
const Label FIRST_LABEL = Label(1, 0, 0);
const Label LAST_LABEL = Label(LABEL_MAX_TYPE_VALUE, LABEL_MAX_TYPE_VALUE, LABEL_MAX_TYPE_VALUE);

// generate next Label
Label nextLabel(const Label& lab);

// table (LUT) used to merge segments
class LabelTable
{
public:
	void setLabel(const Label& vec, const Label& lab);
	Label getLabel(const Label& vec);
private:
	std::map<Label, Label, Comparator<Label> > table_;
};

cv::Mat indexSegments(const cv::Mat& image);

#endif /* SEGMENTATION_H_ */
