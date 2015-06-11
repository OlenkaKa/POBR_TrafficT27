/*
 * Parameters.h
 *
 *  Created on: 11 cze 2015
 *      Author: ola
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <opencv2/opencv.hpp>

struct ShapeParameters
{
	double minW3;
	double maxW3;

	double minM7;
	double maxM7;

	ShapeParameters(double minW3_, double maxW3_, double minM7_, double maxM7_):
		minW3(minW3_), maxW3(maxW3_), minM7(minM7_), maxM7(maxM7_) {
	}
};

struct Parameters {
	cv::Vec3f minHSV;
	cv::Vec3f maxHSV;
	int morphologyIter;
	int minSegmentSize;
	int maxSegmentSize;
	ShapeParameters shapeParams;

	Parameters(cv::Vec3f minHSV_, cv::Vec3f maxHSV_,
			int morphologyIter_, int minSegmentSize_, int maxSegmentSize_,
			double minW3_, double maxW3_, double minM7_, double maxM7_):
		minHSV(minHSV_), maxHSV(maxHSV_),
		morphologyIter(morphologyIter_), minSegmentSize(minSegmentSize_), maxSegmentSize(maxSegmentSize_),
		shapeParams(minW3_, maxW3_, minM7_, maxM7_) {
	}
};

#endif /* PARAMETERS_H_ */
