/*
 * Object.cpp
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#include <map>
#include <cmath>

#include "Object.h"
#include "Segmentation.h"

using namespace cv;
using namespace std;

Object::Object(): minPoint_(INT_MAX, INT_MAX), maxPoint_(0, 0),
		L_(0), M1_(0), M2_(0), M7_(0), W3_(0) {
	for(int i = 0; i < GEOMETRIC_MOMENTS; ++i)
		for(int j = 0; j < GEOMETRIC_MOMENTS; ++j)
			m_[i][j] = 0;
}

long Object::getSize() const {
	return m_[0][0];
}

long Object::getCircuit() const {
	return L_;
}

double Object::getM1() const {
	return M1_;
}

double Object::getM2() const {
	return M2_;
}

double Object::getM7() const {
	return M7_;
}

double Object::getW3() const {
	return W3_;
}

Point Object::getCenter() const {
	return Point(m_[1][0]/m_[0][0], m_[0][1]/m_[0][0]);
}

Point Object::getMinPoint() const {
	return minPoint_;
}

Point Object::getMaxPoint() const {
	return maxPoint_;
}

void Object::addPoint(int x, int y, bool circuit) {
	if(x > maxPoint_.x)
		maxPoint_.x = x;
	if(x < minPoint_.x)
		minPoint_.x = x;
	if(y > maxPoint_.y)
		maxPoint_.y = y;
	if(y < minPoint_.y)
		minPoint_.y = y;
	if(circuit) ++L_;

	for(int i = 0; i < GEOMETRIC_MOMENTS; ++i)
		for(int j = 0; j < GEOMETRIC_MOMENTS; ++j)
			m_[i][j] += calculateGeometricMoment(x, y, i, j);
}

void Object::extractFeatures() {
	long double M11, M02, M20, M12, M21, M03, M30;
	Point center = getCenter();
	M11 = m_[1][1] - m_[1][0] * m_[0][1] / m_[0][0];
	M02 = m_[0][2] - pow(m_[0][1], 2) / m_[0][0];
	M20 = m_[2][0] - pow(m_[1][0], 2) / m_[0][0];
	M12 = m_[1][2] - 2 * m_[1][1] * center.y - m_[0][2] * center.x + 2 * m_[1][0] * pow(center.y, 2);
	M21 = m_[2][1] - 2 * m_[1][1] * center.x - m_[2][0] * center.y + 2 * m_[0][1] * pow(center.x, 2);
	M03 = m_[0][3] - 3 * m_[0][2] * center.y + 2 * m_[0][1] * pow(center.y, 2);
	M30 = m_[3][0] - 3 * m_[2][0] * center.x + 2 * m_[1][0] * pow(center.x, 2);

	M1_ = (M20 + M02) / pow(m_[0][0], 2);
	M2_ = (pow(M20 - M02, 2) + 4 * pow(M11, 2)) / pow(m_[0][0], 4);
	M7_ = (M20 * M02 - pow(M11, 2)) / pow(m_[0][0], 4);

	W3_ = (L_ / (2 * sqrt(M_PI * m_[0][0]))) - 1;
}

void Object::drawOnImage(cv::Mat& image, const cv::Scalar& color) {
	rectangle(image, minPoint_, maxPoint_, color, 5);
}

long long Object::calculateGeometricMoment(int x, int y, int i, int j) {
	return (pow(x, i) * pow(y, j));
}

void Object::generateObjects(const cv::Mat& image_, list<Object>& objects, int minSize, int maxSize) {
	map<Label, Object, Comparator<Label> > map;
	Mat_<Label> image = image_;
	Label lab;

	for(int i = 1; i < image.rows-1; ++i)
		for(int j = 1; j < image.cols-1; ++j) {
			lab = image(i, j);

			if(lab != BACKGROUND) {
				if(map.find(lab) == map.end())
					map[lab] = Object();

				if(image(i-1,j-1) != lab || image(i-1,j) != lab ||
						image(i-1,j+1) != lab || image(i,j-1) != lab ||
						image(i,j+1) != lab || image(i+1,j-1) != lab ||
						image(i+1,j) != lab || image(i+1,j+1) != lab)
					map[lab].addPoint(j, i, true);
				else
					map[lab].addPoint(j, i, false);
			}
		}

	auto endIt = map.end();
	for(auto it = map.begin(); it != endIt; ++it) {
		Object* obj = &(it->second);
		if(obj->getSize() > minSize && obj->getSize() < maxSize) {
			obj->extractFeatures();
			objects.push_back(*obj);
		}
	}
}

ostream& operator<< (ostream& os, const Object& obj) {
	os << "    --- Object ---" << endl
			<< "    M1: " << obj.getM1() << endl
			<< "    M2: " << obj.getM2() << endl
			<< "    M7: " << obj.getM7() << endl
			<< "    W3: " << obj.getW3() << endl
			<< "    Size: " << obj.getSize() << endl
			<< "    Circuit: " << obj.getCircuit() << endl
			<< "    Center: " << obj.getCenter() << endl
			<< "    Min point: " << obj.getMinPoint() << endl
			<< "    Max point: " << obj.getMaxPoint();
	return os;
}
