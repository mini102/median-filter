
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void median(const cv::Mat& src, int window, cv::Mat& dst) {

	std::vector<uchar> neighbors;

	for (auto i = 0;i < dst.rows;i++) {
		for (auto j = 0; j < dst.cols;j++) {
			for (auto y = -window; y <= window;y++) for (auto x = -window; x <= window;x++) {
					neighbors.push_back(src.at<uchar>(min(src.rows-1,max(0,i+y)), min(src.cols-1, max(0, j+x))));
			}
			std::sort(neighbors.begin(), neighbors.end()); 

			dst.at<uchar>(i, j) = neighbors[neighbors.size() / 2];
			neighbors.clear();
		}
		}
	}

int main(int ac, char** av) {

	Mat img = imread("MedianFilterInput.png",0); //두번째 파라미터로 0주면 흑백으로 read 
	Mat img2(Size(img.rows, img.cols), CV_8U);
	for (int i = 1;i < 6;i++) {  //창을 닫으면 window가 증가된 img 나옴
		median(img, i, img2);
		imshow("img", img2);
		waitKey(0);
	}
	return 0;

}

