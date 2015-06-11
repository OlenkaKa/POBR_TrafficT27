#include <opencv2/opencv.hpp>

#include "TrafficT27.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Usage: "<< argv[0] <<" <Image_Path>\n";
		return -1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		cout << "Could not open or find the image\n";
		return -1;
	}

	Mat resultImage = findTrafficT27(image);

	namedWindow("Input Image", WINDOW_NORMAL);
	imshow("Input Image", image);

	namedWindow("Output Image", WINDOW_NORMAL);
	imshow("Output Image", resultImage);

	waitKey(0);
    return 0;
}
