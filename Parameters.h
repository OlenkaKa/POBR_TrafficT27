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
	double minM1;
	double maxM1;

	double minM2;
	double maxM2;

	double minM3;
	double maxM3;

	double minM7;
	double maxM7;

	double minW3;
	double maxW3;

	ShapeParameters(double minM1_, double maxM1_,
			double minM2_, double maxM2_,
			double minM3_, double maxM3_,
			double minM7_, double maxM7_,
			double minW3_, double maxW3_):
		minM1(minM1_), maxM1(maxM1_),
		minM2(minM2_), maxM2(maxM2_),
		minM3(minM3_), maxM3(maxM3_),
		minM7(minM7_), maxM7(maxM7_),
		minW3(minW3_), maxW3(maxW3_) {
	}
};

struct RelationParameters
{
	double minSizeRelation;
	double maxSizeRelation;

	cv::Vec2d minVector;
	cv::Vec2d maxVector;

	RelationParameters(double minSize_, double maxSize_,
			const cv::Vec2d& minVec_, const cv::Vec2d& maxVec_):
				minSizeRelation(minSize_), maxSizeRelation(maxSize_),
				minVector(minVec_), maxVector(maxVec_) {
	}
};

struct Parameters {
	cv::Vec3f minHSV;
	cv::Vec3f maxHSV;
	int morphologyCloseIter;
	int morphologyOpenIter;
	int minSegmentSize;
	int maxSegmentSize;
	ShapeParameters shapeParams;

	Parameters(cv::Vec3f minHSV_, cv::Vec3f maxHSV_,
			int morphologyOpenIter_, int morphologyCloseIter_,
			int minSegmentSize_, int maxSegmentSize_,
			double minM1_, double maxM1_,
			double minM2_, double maxM2_,
			double minM3_, double maxM3_,
			double minM7_, double maxM7_,
			double minW3_, double maxW3_):
		minHSV(minHSV_), maxHSV(maxHSV_),
		morphologyOpenIter(morphologyOpenIter_), morphologyCloseIter(morphologyCloseIter_),
		minSegmentSize(minSegmentSize_), maxSegmentSize(maxSegmentSize_),
		shapeParams(minM1_, maxM1_, minM2_, maxM2_, minM3_, maxM3_, minM7_, maxM7_, minW3_, maxW3_) {
	}
};

#endif /* PARAMETERS_H_ */
