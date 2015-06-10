/*
 * Object.cpp
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#include <map>

#include "Object.h"
#include "Segmentation.h"

using namespace cv;
using namespace std;

void Object::add(uchar x, uchar y) {
	// TODO
}

void Object::extractFeatures() {
	// TODO
}

vector<Object> Object::generateObjects(const cv::Mat& image_) {
	map<Label, Object, Comparator<Label> > map;
	Mat_<Vec3b> image = image_;
	Label lab;

	for(int i = 0; i < image.rows; ++i)
		for(int j = 0; j < image.cols; ++j) {
			lab = getLabel(image(i, j));
			if(lab != BACKGROUND) {
				if(map.find(lab) == map.end())
					map[lab] = Object();
				map[lab].add(i, j);
			}
		}

	vector<Object> result;
	auto end_it = map.end();
	for(auto it = map.begin(); it != end_it; ++it) {
		(it->second).extractFeatures();
		result.push_back(it->second);
	}
	return result;
}
