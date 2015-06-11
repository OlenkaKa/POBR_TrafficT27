/*
 * Segmentation.cpp
 *
 *  Created on: 10 cze 2015
 *      Author: ola
 */

#include "Segmentation.h"

using namespace cv;
using namespace std;

Label nextLabel(const Label& lab) {
	Label result = lab;
	if(lab[0] < LABEL_MAX_TYPE_VALUE)
		++result[0];
	else if(lab[1] < LABEL_MAX_TYPE_VALUE)
		++result[1];
	else if(lab[2] < LABEL_MAX_TYPE_VALUE)
		++result[2];
	else
		cerr << "Segmentation error: to many labels!" << endl;
	return result;
}

void LabelTable::setLabel(const Label& vec, const Label& lab) {
	table_[vec] = lab;
}

Label LabelTable::getLabel(const Label& vec) {
	auto it = table_.find(vec);
	if(it == table_.end())
		return BACKGROUND;
	return it->second;
}

Mat indexSegments(const Mat& image_) {
	Mat result_ = Mat::zeros(image_.rows, image_.cols, LABEL_TYPE);
	Mat_<uchar> image = image_;
	Mat_<Label> result = result_;
	Label minLab, maxLab, currLab = FIRST_LABEL;
	LabelTable table;

	for(int i = 1; i < image.rows-1; ++i)
		for(int j = 1; j < image.cols-1; ++j) {
			if(image(i, j) == 0)
				continue;
			Label nLabs[4] = {result(i, j-1), result(i-1, j-1), result(i-1, j), result(i-1, j+1)};
			if(nLabs[0] == nLabs[1] && nLabs[0] == nLabs[2] &&
					nLabs[0] == nLabs[3] && nLabs[0] == BACKGROUND) {
				result(i, j) = currLab;
				table.setLabel(result(i, j), currLab);
				currLab = nextLabel(currLab);
			}
			else {
				minLab = LAST_LABEL;
				maxLab = FIRST_LABEL;

				for(int i = 0; i < 4; ++i)
					if(nLabs[i] != BACKGROUND) {
						if(isLess<Label>(nLabs[i], minLab))
							minLab = nLabs[i];
						if(isLess<Label>(maxLab, nLabs[i]))
							maxLab = nLabs[i];
					}
				result(i, j) = minLab;
				table.setLabel(maxLab, table.getLabel(minLab));
			}
		}
	for(int i = 1; i < result.rows-1; ++i)
		for(int j = 1; j < result.cols-1; ++j)
			result(i, j) = table.getLabel(result(i, j));

	return result;
}
