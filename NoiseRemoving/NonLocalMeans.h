#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
using namespace cv;

//---------------------------------------NON-LOCAL MEANS FILTER-----------------------------------------------

void nonlocalMeansFilter(Mat& src, Mat& dest, int templeteWindowSize, int searchWindowSize, double h, double sigma = 0.0)
{
	if (templeteWindowSize > searchWindowSize)
	{
		return;
	}
	if (dest.empty())dest = Mat::zeros(src.size(), src.type());

	const int tr = templeteWindowSize >> 1;
	const int sr = searchWindowSize >> 1;
	const int bb = sr + tr;
	const int D = searchWindowSize*searchWindowSize;
	const int H = D / 2 + 1;
	const double div = 1.0 / (double)D;//search area div
	const int tD = templeteWindowSize*templeteWindowSize;
	const double tdiv = 1.0 / (double)(tD);//templete square div

	Mat im;
	copyMakeBorder(src, im, bb, bb, bb, bb, cv::BORDER_DEFAULT);

	//weight computation;
	std::vector<double> weight(256 * 256 * src.channels());
	double* w = &weight[0];
	const double gauss_sd = (sigma == 0.0) ? h : sigma;
	double gauss_color_coeff = -(1.0 / (double)(src.channels()))*(1.0 / (h*h));
	int emax;
	for (int i = 0; i < 256 * 256 * src.channels(); i++)
	{
		double v = std::exp(max(i - 2.0*gauss_sd*gauss_sd, 0.0)*gauss_color_coeff);
		w[i] = v;
		if (v < 0.001)
		{
			emax = i;
			break;
		}
	}
	for (int i = emax; i < 256 * 256 * src.channels(); i++)w[i] = 0.0;

	if (src.channels() == 3)
	{
		const int cstep = im.step - templeteWindowSize * 3;
		const int csstep = im.step - searchWindowSize * 3;
		for (int j = 0;j < src.rows;j++)
		{
			uchar* d = dest.ptr(j);
			int* ww = new int[D];
			double* nw = new double[D];
			for (int i = 0;i < src.cols;i++)
			{
				double tweight = 0.0;
				//search loop
				uchar* tprt = im.data + im.step*(sr + j) + 3 * (sr + i);
				uchar* sptr2 = im.data + im.step*j + 3 * i;
				for (int l = searchWindowSize, count = D - 1;l--;)
				{
					uchar* sptr = sptr2 + im.step*(l);
					for (int k = searchWindowSize;k--;)
					{
						//templete loop
						int e = 0;
						uchar* t = tprt;
						uchar* s = sptr + 3 * k;
						for (int n = templeteWindowSize;n--;)
						{
							for (int m = templeteWindowSize;m--;)
							{
								// computing color L2 norm
								e += (s[0] - t[0])*(s[0] - t[0]) + (s[1] - t[1])*(s[1] - t[1]) + (s[2] - t[2])*(s[2] - t[2]);//L2 norm
								s += 3, t += 3;
							}
							t += cstep;
							s += cstep;
						}
						const int ediv = e*tdiv;
						ww[count--] = ediv;
						//get weighted Euclidean distance
						tweight += w[ediv];
					}
				}
				//weight normalization
				if (tweight == 0.0)
				{
					for (int z = 0;z < D;z++) nw[z] = 0;
					nw[H] = 1;
				}
				else
				{
					double itweight = 1.0 / (double)tweight;
					for (int z = 0;z < D;z++) nw[z] = w[ww[z]] * itweight;
				}

				double r = 0.0, g = 0.0, b = 0.0;
				uchar* s = im.ptr(j + tr); s += 3 * (tr + i);
				for (int l = searchWindowSize, count = 0;l--;)
				{
					for (int k = searchWindowSize;k--;)
					{
						r += s[0] * nw[count];
						g += s[1] * nw[count];
						b += s[2] * nw[count++];
						s += 3;
					}
					s += csstep;
				}
				d[0] = saturate_cast<uchar>(r);
				d[1] = saturate_cast<uchar>(g);
				d[2] = saturate_cast<uchar>(b);
				d += 3;
			}
			delete[] ww;
			delete[] nw;
		}
	}
	else if (src.channels() == 1)
	{
		const int cstep = im.step - templeteWindowSize;
		const int csstep = im.step - searchWindowSize;
		for (int j = 0;j < src.rows;j++)
		{
			uchar* d = dest.ptr(j);
			int* ww = new int[D];
			double* nw = new double[D];
			for (int i = 0;i < src.cols;i++)
			{
				double tweight = 0.0;
				//search loop
				uchar* tprt = im.data + im.step*(sr + j) + (sr + i);
				uchar* sptr2 = im.data + im.step*j + i;
				for (int l = searchWindowSize, count = D - 1;l--;)
				{
					uchar* sptr = sptr2 + im.step*(l);
					for (int k = searchWindowSize;k--;)
					{
						//templete loop
						int e = 0;
						uchar* t = tprt;
						uchar* s = sptr + k;
						for (int n = templeteWindowSize;n--;)
						{
							for (int m = templeteWindowSize;m--;)
							{
								// computing color L2 norm
								e += (*s - *t)*(*s - *t);
								s++, t++;
							}
							t += cstep;
							s += cstep;
						}
						const int ediv = e*tdiv;
						ww[count--] = ediv;
						//get weighted Euclidean distance
						tweight += w[ediv];
					}
				}
				//weight normalization
				if (tweight == 0.0)
				{
					for (int z = 0;z < D;z++) nw[z] = 0;
					nw[H] = 1;
				}
				else
				{
					double itweight = 1.0 / (double)tweight;
					for (int z = 0;z < D;z++) nw[z] = w[ww[z]] * itweight;
				}

				double v = 0.0;
				uchar* s = im.ptr(j + tr); s += (tr + i);
				for (int l = searchWindowSize, count = 0;l--;)
				{
					for (int k = searchWindowSize;k--;)
					{
						v += *(s++)*nw[count++];
					}
					s += csstep;
				}
				*(d++) = saturate_cast<uchar>(v);
			}
			delete[] ww;
			delete[] nw;
		}
	}
}
