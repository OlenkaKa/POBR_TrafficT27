#include <iostream>
#include <cmath>

#include "CommonFunctions.h"

using namespace cv;
using namespace std;

void convertHSV(const Mat& _image)
{
	Mat_<Vec3b> image = _image;
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

Mat selectColor(const Mat& image_, const Vec3b& minValues, const Vec3b& maxValues)
{
	Mat result_(image_.size(), CV_8UC3);
	Mat_<Vec3b> image = image_;
	Mat_<Vec3b> result = result_;

	for(int i = 0; i < image.rows; ++i)
		for(int j = 0; j < image.cols; ++j)
			if(image(i,j)[0] >= minValues[0] && image(i,j)[0] <= maxValues[0] &&
					image(i,j)[1] >= minValues[1] && image(i,j)[1] <= maxValues[1] &&
					image(i,j)[2] >= minValues[2] && image(i,j)[2] <= maxValues[2])
				result(i,j) = Vec3b(255, 255, 255);

	return result;
}
