/*
 * Objects.h
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <opencv2/opencv.hpp>

const int GEOMETRIC_MOMENTS = 4;

class Object
{
public:
	Object();

	long getSize() const;
	long getCircuit() const;
	double getM1() const;
	double getM2() const;
	double getM7() const;
	double getW3() const;
	cv::Point getCenter() const;
	cv::Point getMinPoint() const;
	cv::Point getMaxPoint() const;

	void addPoint(int x, int y, bool circuit);
	void extractFeatures();

	void drawOnImage(cv::Mat& image, const cv::Scalar& color);

	static void generateObjects(const cv::Mat& image, std::list<Object>& objects,
			int minSize = 0, int maxSize = INT_MAX);

	friend std::ostream& operator<< (std::ostream& os, const Object& obj);

private:
	long long calculateGeometricMoment(int x, int y, int i, int j);

	// object localization
	cv::Point minPoint_;
	cv::Point maxPoint_;

	// geometric moments
	long long m_[GEOMETRIC_MOMENTS][GEOMETRIC_MOMENTS];

	// coefficients
	int L_;
	double M1_;
	double M2_;
	double M7_;
	double W3_;
};

#endif /* OBJECT_H_ */
