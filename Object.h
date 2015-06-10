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

const int GEOMETRIC_MOMENTS = 3;

class Object
{
public:
	Object();
	int getSize();
	int getCircuit();
	cv::Point getCenter();
	double getM7();
	double getW3();

	void addPoint(int x, int y, bool circuit);
	void extractFeatures();

	static void generateObjects(const cv::Mat& image, std::vector<Object>& objects,
			int minSize = 0, int maxSize = INT_MAX);

private:
	long long calculateGeometricMoment(int i, int j, int powI, int powJ);

	// object localization
	cv::Point minPoint_;
	cv::Point maxPoint_;

	// geometric moments
	long long m_[GEOMETRIC_MOMENTS][GEOMETRIC_MOMENTS];

	// coefficients
	int L_;
	double M7_;
	double W3_;
};

#endif /* OBJECT_H_ */
