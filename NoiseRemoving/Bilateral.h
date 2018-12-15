#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
using namespace cv;

//---------------------------------------BILATERAL FILTER-----------------------------------------------

float distance(int x, int y, int i, int j)
{
	return float(sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

double gaussian(float x, double sigma)
{
	return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * CV_PI * pow(sigma, 2));
}

void applyBilateralFilter(Mat& source, Mat& filteredImage, int x, int y, int diameter, double sigmaI, double sigmaS)
{
	double iFiltered = 0;
	double wP = 0;
	int neighbor_x = 0;
	int neighbor_y = 0;
	int half = diameter / 2;

	for (int i = 0; i < diameter; i++)
	{
		for (int j = 0; j < diameter; j++)
		{
			neighbor_x = x - (half - i);
			if (neighbor_x < 0 || source.rows <= neighbor_x)
				neighbor_x = x;

			neighbor_y = y - (half - j);
			if (neighbor_y < 0 || source.cols <= neighbor_y)
				neighbor_y = y;

			double gi = gaussian(source.at<uchar>(neighbor_x, neighbor_y) - source.at<uchar>(x, y), sigmaI);
			double gs = gaussian(distance(x, y, neighbor_x, neighbor_y), sigmaS);
			double w = gi * gs;
			iFiltered = iFiltered + source.at<uchar>(neighbor_x, neighbor_y) * w;
			wP = wP + w;
		}
	}
	iFiltered = iFiltered / wP;
	filteredImage.at<double>(x, y) = iFiltered;
}

Mat bilateralFilterOwn(Mat& source, int diameter, double sigmaI, double sigmaS)
{
	Mat filteredImage = Mat::zeros(source.rows, source.cols, CV_64F);
	int width = source.cols;
	int height = source.rows;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			applyBilateralFilter(source, filteredImage, i, j, diameter, sigmaI, sigmaS);
		}
	}
	return filteredImage;
}
