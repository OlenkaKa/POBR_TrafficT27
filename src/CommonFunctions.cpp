#include <iostream>
#include <cmath>
#include <map>

#include "CommonFunctions.h"

using namespace cv;
using namespace std;

const Vec3b BLACK_VEC(0, 0, 0);
const Vec3b WHITE_VEC(255, 255, 255);

void convertHSV(const Mat& image_)
{
	Mat_<Vec3b> image = image_;
	double B, G, R, V, H, diff;

	for(int i = 0; i < image.rows; ++i)
		for(int j = 0; j < image.cols; ++j)
		{
			B = image(i, j)[0];
			G = image(i, j)[1];
			R = image(i, j)[2];

			// V channel
			image(i, j)[2] = V = max(max(B, G), R);

			// S channel
			diff = V - min(min(B, G), R);
			image(i, j)[1] = (V != 0) ? (255 * diff / V) : 0;

			// H channel
			if(diff != 0)
			{
				if(V == B)
					H = 240 + 60 * (R-G)/diff;
				else if(V == G)
					H = 120 + 60 * (B-R)/diff;
				else
					H = 60 * (G-B)/diff;

				if(H < 0) H += 360;
				image(i, j)[0] = H / 2;
			}
		}
}

bool isLess(const Vec3f& v1, const Vec3f& v2)
{
	if(v1[0] < v2[0])
		return true;
	if(v1[0] > v2[0])
		return false;
	if(v1[1] < v2[1])
		return true;
	if(v1[1] > v2[1])
		return false;
	if(v1[2] < v2[2])
		return true;
	return false;
}

/*
 * SEGMENTATION
 */

void nextLabel(Vec3b& label) {
	if(label[0] < 255)
		++label[0];
	else if(label[1] < 255)
		++label[1];
	else if(label[2] < 254)
		++label[2];
	else
		cerr << "Error: to many labels!" << endl;
}

class LabelTable
{
public:
	Vec3f operator[](const Vec3f& v) {
		auto iterator = table_.find(v);
		if(iterator == table_.end())
			return WHITE_VEC;
		return iterator->second;
	}
	void setValue(const Vec3f& idx, const Vec3f& val) {
		table_[idx] = val;
	}
private:
	struct Comparator
	{
		bool operator() (Vec3b a, Vec3b b) {
			return isLess(a, b);
	    }
	};
	map<Vec3b, Vec3b, Comparator> table_;
};

Mat indexSegments(const Mat& image_)
{
	Mat result_(image_.rows, image_.cols, CV_8UC3);
	Mat_<Vec3b> image = image_;
	Mat_<Vec3b> result = result_;
	LabelTable mergeTable;
	Vec3b minLabel, maxLabel, currLabel(0, 0, 0);

	for(int i = 0; i < result.rows; ++i)
		for(int j = 0; j < result.cols; ++j)
			result(i, j) = WHITE_VEC;

	for(int i = 1; i < image.rows-1; ++i)
		for(int j = 1; j < image.cols-1; ++j) {
			if(image(i, j) == BLACK_VEC)
				continue;

			Vec3b neighbours[4] = {result(i, j-1), result(i-1, j-1), result(i-1, j), result(i-1, j+1)};

			if(neighbours[0] == neighbours[1] && neighbours[0] == neighbours[2] &&
					neighbours[0] == neighbours[3] && neighbours[0] == WHITE_VEC) {
				result(i, j) = currLabel;
				mergeTable.setValue(currLabel, currLabel);
				nextLabel(currLabel);
			}
			else {
				minLabel = Vec3b(255, 255, 255);
				maxLabel = Vec3b(0, 0, 0);
				for(int i = 0; i < 4; ++i) {
					if(neighbours[i] != WHITE_VEC) {
						if(isLess(neighbours[i], minLabel))
							minLabel = neighbours[i];
						if(isLess(maxLabel, neighbours[i]))
							maxLabel = neighbours[i];
					}
				}
				result(i, j) = mergeTable[minLabel];
				mergeTable.setValue(maxLabel, mergeTable[minLabel]);
			}

		}

	for(int i = 1; i < result.rows-1; ++i)
		for(int j = 1; j < result.cols-1; ++j)
			result(i, j) = mergeTable[result(i, j)];

	return result;
}

/*
 * SELECT COLOR
 */

bool checkLessMin(uchar min, uchar max, uchar value)
{
	if(value >= min && value <= max)
		return true;
	return false;
}
bool checkLessMax(uchar min, uchar max, uchar value)
{
	if(value >= min || value <= max)
		return true;
	return false;
}

Mat selectColor(const Mat& image_, const Vec3b& minValues, const Vec3b& maxValues)
{
	Mat result_(image_.rows, image_.cols, CV_8UC3);
	Mat_<Vec3b> image = image_;
	Mat_<Vec3b> result = result_;
	bool(*check0)(uchar, uchar, uchar);
	bool(*check1)(uchar, uchar, uchar);
	bool(*check2)(uchar, uchar, uchar);

	if(minValues[0] <= maxValues[0])
		check0 = &checkLessMin;
	else
		check0 = &checkLessMax;
	if(minValues[1] <= maxValues[1])
		check1 = &checkLessMin;
	else
		check1 = &checkLessMax;
	if(minValues[2] <= maxValues[2])
		check2 = &checkLessMin;
	else
		check2 = &checkLessMax;

	for(int i = 0; i < image.rows; ++i)
		for(int j = 0; j < image.cols; ++j)
			if(check0(minValues[0], maxValues[0], image(i,j)[0]) &&
					check1(minValues[1], maxValues[1], image(i,j)[1]) &&
					check2(minValues[2], maxValues[2], image(i,j)[2]))
				result(i,j) = WHITE_VEC;
	return result;
}
