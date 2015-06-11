/*
 * Consts.h
 *
 *  Created on: 9 cze 2015
 *      Author: ola
 */

#ifndef CONSTS_H_
#define CONSTS_H_

#include "Parameters.h"

const Parameters BACKGROUND_PARAMS(
		// HSV values
		cv::Vec3b(17, 173, 165), cv::Vec3b(28, 255, 255),
		// Morphology iterations
		3,
		// Segment size
		600, INT_MAX,
		// M1
		0.0, 1000.0,
		// M7
		0.01, 0.02,
		// W3
		1.6, 2.1);

const Parameters CIRCLE_PARAMS(
		cv::Vec3b(170, 170, 150), cv::Vec3b(3, 255, 255),
		3,
		400, INT_MAX,
		0.0, 1000.0,
		0.006, 0.007,
		0.2, 0.3);

const Parameters GIRL_PARAMS(
		cv::Vec3b(0, 0, 0), cv::Vec3b(255, 255, 60),
		3,
		600, 70000,
		0.0, 1000.0,
		0.001, 0.25,
		2.0, 3.0);

const Parameters STICK_PARAMS(
		cv::Vec3b(0, 0, 150), cv::Vec3b(100, 100, 255),
		3,
		600, INT_MAX,
		0.0, 1000.0,
		0.01, 0.03,
		0.0, 1.5);

#endif /* CONSTS_H_ */
