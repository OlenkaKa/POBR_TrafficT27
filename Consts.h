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
		2, 1,
		// Segment size
		300, INT_MAX,
		// M1
		0.2, 0.25,
		// M2
		-100, 111,
		// M3
		-100, 111,
		// M7
		0.01, 0.02,
		// W3
		-100.0, 100.0);

const Parameters CIRCLE_PARAMS(
		// HSV values
		cv::Vec3b(170, 170, 150), cv::Vec3b(3, 255, 255),
		// Morphology iterations
		3, 3,
		// Segment size
		400, INT_MAX,
		// M1
		0.0, 0.2,
		// M2
		0.0, 0.1,
		// M3
		-100, 111,
		// M7
		0.0, 0.1,
		// W3
		0, 100.0);

const Parameters GIRL_PARAMS(
		// HSV values
		cv::Vec3b(0, 0, 0), cv::Vec3b(255, 255, 100),
		// Morphology iterations
		0, 2,
		// Segment size
		500, 70000,
		// M1
		0.3, 0.45,
		// M2
		0.0, 0.1,
		// M3
		0.0, 0.1,
		// M7
		0.0, 0.3,
		// W3
		0, 100);

const Parameters STICK_PARAMS(
		// HSV values
		cv::Vec3b(0, 0, 150), cv::Vec3b(255, 100, 255),
		// Morphology iterations
		0, 0,
		// Segment size
		0, 10000,
		// M1
		0.6, 0.8,
		// M2
		0.1, 0.3,
		// M3
		-100, 111,
		// M7
		0.0, 0.15,
		// W3
		-1000, 1000);

const RelationParameters BACKGROUND_CIRCLE_REL(
		0.002, 0.035);

const RelationParameters BACKGROUND_GIRL_REL(
		0.1, 0.25);

const RelationParameters BACKGROUND_STICK_REL(
		0.01, 0.04);

#endif /* CONSTS_H_ */
