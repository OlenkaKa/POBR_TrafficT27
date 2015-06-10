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

Object::Object(): minPoint_(0, 0), maxPoint_(INT_MAX, INT_MAX),
		L_(0), M7_(0), W3_(0) {
	for(int i = 0; i < GEOMETRIC_MOMENTS; ++i)
		for(int j = 0; j < GEOMETRIC_MOMENTS; ++j)
			m_[i][j] = 0;
}

int Object::getSize() {
	return m_[0][0];
}

int Object::getCircuit() {
	return L_;
}

Point Object::getCenter() {
	return Point(m_[1][0]/m_[0][0], m_[0][1]/m_[0][0]);
}

double Object::getM7() {
	return M7_;
}

double Object::getW3() {
	return W3_;
}

void Object::addPoint(int x, int y, bool circuit) {
	if(x > maxPoint_.x)
		maxPoint_.x = x;
	if(x < minPoint_.x)
		minPoint_.x = x;
	if(y > maxPoint_.y)
		maxPoint_.y = y;
	if(x < minPoint_.y)
		minPoint_.y = y;
	if(circuit) ++L_;

	for(int i = 0; i < GEOMETRIC_MOMENTS; ++i)
		for(int j = 0; j < GEOMETRIC_MOMENTS; ++j)
			m_[i][j] += calculateGeometricMoment(x, y, i, j);
}

void Object::extractFeatures() {
	long double M02, M20, M11;
	M11 = m_[1][1] - m_[1][0] * m_[0][1] / m_[0][0];
	M20 = m_[2][0] - pow(m_[1][0], 2) / m_[0][0];
	M02 = m_[0][2] - pow(m_[0][1], 2) / m_[0][0];

	M7_ = (M20 * M02 - pow(M11, 2)) / pow(m_[0][0], 4);
	//cout << "M7: " << M7_ << endl;

	W3_ = (L_ / (2 * sqrt(M_PI * m_[0][0]))) - 1;
	//cout << "W3: " << W3_ << endl;
}

long long Object::calculateGeometricMoment(int x, int y, int i, int j) {
	return (pow(x, i) * pow(y, j));
}

void Object::generateObjects(const cv::Mat& image_, vector<Object>& objects, int minSize, int maxSize) {
	map<Label, Object, Comparator<Label> > map;
	Mat_<Vec3b> image = image_;
	Label lab;

	for(int i = 1; i < image.rows-1; ++i)
		for(int j = 1; j < image.cols-1; ++j) {
			lab = getLabel(image(i, j));

			if(lab != BACKGROUND) {
				if(map.find(lab) == map.end())
					map[lab] = Object();

				if(getLabel(image(i-1,j-1)) != lab || getLabel(image(i-1,j)) != lab ||
						getLabel(image(i-1,j+1)) != lab || getLabel(image(i,j-1)) != lab ||
						getLabel(image(i,j+1)) != lab || getLabel(image(i+1,j-1)) != lab ||
						getLabel(image(i+1,j)) != lab || getLabel(image(i+1,j+1)) != lab)
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
