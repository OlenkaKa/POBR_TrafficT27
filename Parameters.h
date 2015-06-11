/*
 * Parameters.h
 *
 *  Created on: 11 cze 2015
 *      Author: ola
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <opencv2/opencv.hpp>

struct Parameters {
	cv::Vec3f minHSV;
	cv::Vec3f maxHSV;
	int minSegmentSize;
	int maxSegmentSize;

	Parameters(cv::Vec3f minHSV_, cv::Vec3f maxHSV_, int minSegmentSize_, int maxSegmentSize_):
		minHSV(minHSV_), maxHSV(maxHSV_), minSegmentSize(minSegmentSize_), maxSegmentSize(maxSegmentSize_) {
	}
};

#endif /* PARAMETERS_H_ */
