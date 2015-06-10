/*
 * Objects.h
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <opencv2/opencv.hpp>
#include <vector>

class Object
{
public:
	static std::vector<Object> generateObjects(const cv::Mat& image);
private:
	void add(uchar x, uchar y);
	void extractFeatures();
};

#endif /* OBJECT_H_ */
