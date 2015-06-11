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
		cv::Vec3b(17, 173, 165), cv::Vec3b(28, 255, 255),
		600, INT_MAX,
		0, 0,
		0, 0);

const Parameters CIRCLE_PARAMS(
		cv::Vec3b(170, 170, 150), cv::Vec3b(3, 255, 255),
		400, INT_MAX,
		0.2, 0.3,
		0.006, 0.007);

const Parameters GIRL_PARAMS(
		cv::Vec3b(0, 0, 0), cv::Vec3b(255, 255, 60),
		600, 70000,
		0, 0,
		0, 0);

const Parameters STICK_PARAMS(
		cv::Vec3b(0, 0, 240), cv::Vec3b(255, 50, 255),
		600, INT_MAX,
		0, 0,
		0, 0);

#endif /* CONSTS_H_ */
