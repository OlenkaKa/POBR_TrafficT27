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
		2,
		// Segment size
		600, INT_MAX,
		// M1
		0.2, 0.25,
		// M7
		0.01, 0.02,
		// W3
		0, 100.0);

const Parameters CIRCLE_PARAMS(
		cv::Vec3b(170, 170, 150), cv::Vec3b(3, 255, 255),
		3,
		400, INT_MAX,
		0.0, 1000.0,
		0.006, 0.007,
		0, 100.0);

const Parameters GIRL_PARAMS(
		cv::Vec3b(0, 0, 0), cv::Vec3b(255, 255, 100),
		2,
		600, 70000,
		0.0, 1000.0,
		0.001, 0.9,
		0, 100);

const Parameters STICK_PARAMS(
		cv::Vec3b(0, 0, 150), cv::Vec3b(100, 100, 255),
		3,
		600, INT_MAX,
		0.0, 1000.0,
		0.01, 0.03,
		0.0, 1.5);

const RelationParameters BACKGROUND_CIRCLE_REL(
		0, 0,
		cv::Vec2d(0, 0), cv::Vec2d(0, 0));

const RelationParameters BACKGROUND_GIRL_REL(
		0.1, 0.25,
		cv::Vec2d(0, 0), cv::Vec2d(0, 0));

const RelationParameters BACKGROUND_STICK_REL(
		0, 0,
		cv::Vec2d(0, 0), cv::Vec2d(0, 0));

#endif /* CONSTS_H_ */
