#include <cmath>
#include <algorithm>
#include <array>

#include "Common.h"

using namespace cv;
using namespace std;

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
	Mat result_ = Mat::zeros(image_.rows, image_.cols, CV_8UC1);
	Mat_<Vec3b> image = image_;
	Mat_<uchar> result = result_;
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
				result(i,j) = 255;
	return result;
}

Mat dilate(const Mat& image_, int iterations) {
	Mat result_ = Mat::zeros(image_.rows, image_.cols, CV_8UC1);
	Mat_<uchar> image = image_;
	Mat_<uchar> result = result_;
	Mat_<uchar> tmp = image;

	for(int iter = 0; iter < iterations; ++iter) {
		for(int i = 1; i < result.rows-1; ++i) {
			for(int j = 1; j < result.cols-1; ++j) {
				array<uchar, 9> values = {tmp(i-1, j-1), tmp(i-1, j), tmp(i-1, j+1),
						tmp(i, j-1), tmp(i, j), tmp(i, j+1),
						tmp(i+1, j-1), tmp(i+1, j), tmp(i+1, j+1)};
				result(i, j) = *(max_element(values.begin(), values.end()));
			}
		}
		tmp = result.clone();
	}
	return result;
}

Mat erode(const Mat& image_, int iterations) {
	Mat result_ = Mat::zeros(image_.rows, image_.cols, CV_8UC1);
	Mat_<uchar> image = image_;
	Mat_<uchar> result = result_;
	Mat_<uchar> tmp = image;

	for(int iter = 0; iter < iterations; ++iter) {
		for(int i = 1; i < result.rows-1; ++i) {
			for(int j = 1; j < result.cols-1; ++j) {
				array<uchar, 9> values = {tmp(i-1, j-1), tmp(i-1, j), tmp(i-1, j+1),
						tmp(i, j-1), tmp(i, j), tmp(i, j+1),
						tmp(i+1, j-1), tmp(i+1, j), tmp(i+1, j+1)};
				result(i, j) = *(min_element(values.begin(), values.end()));
			}
		}
		tmp = result.clone();
	}
	return result;
}

Mat morphologyClose(const Mat& image, int iterations) {
	return erode(dilate(image, iterations), iterations);
}

Mat morphologyOpen(const Mat& image, int iterations) {
	return dilate(erode(image, iterations), iterations);
}

Mat sharpenFilter(const Mat& image_, int iterations) {
	Mat result_(image_.rows, image_.cols, CV_8UC3);
	Mat_<Vec3b> image = image_;
	Mat_<Vec3b> result = result_;
	Mat_<Vec3b> tmp = image;
	static const double kernel[9] = {0, -0.5, 0, -0.5, 3, -0.5, 0, -0.5, 0};

	for(int iter = 0; iter < iterations; ++iter) {
		for(int i = 1; i < result.rows-1; ++i) {
			for(int j = 1; j < result.cols-1; ++j) {
				result(i, j) =  tmp(i-1, j-1) * kernel[0] + tmp(i-1, j) * kernel[1] +
						tmp(i-1, j+1) * kernel[2] + tmp(i, j-1) * kernel[3] +
						tmp(i, j) * kernel[4] + tmp(i, j+1) * kernel[5] +
						tmp(i+1, j-1) * kernel[6] + tmp(i+1, j) * kernel[7] +
						tmp(i+1, j+1) * kernel[8];
				for(int k = 0; k < 3; ++k)
					if(result(i, j)[k] < 0)
						result(i, j)[k] = 0;
					else if (result(i, j)[k] > 255)
						result(i, j)[k] = 255;
			}
		}
		tmp = result.clone();
	}
	return result;
}

Mat medianFilter(const Mat& image_, int iterations) {
	Mat result_(image_.rows, image_.cols, CV_8UC3);
	Mat_<Vec3b> image = image_;
	Mat_<Vec3b> result = result_;
	Mat_<Vec3b> tmp = image;

	for(int iter = 0; iter < iterations; ++iter) {
		for(int i = 1; i < result.rows-1; ++i) {
			for(int j = 1; j < result.cols-1; ++j) {
				array<Vec3b, 9> values = {tmp(i-1, j-1), tmp(i-1, j), tmp(i-1, j+1),
						tmp(i, j-1), tmp(i, j), tmp(i, j+1),
						tmp(i+1, j-1), tmp(i+1, j), tmp(i+1, j+1)};
				sort(values.begin(), values.end(), isLess<Vec3b>);
				result(i, j) =  values[5];
			}
		}
		tmp = result.clone();
	}
	return result;
}
