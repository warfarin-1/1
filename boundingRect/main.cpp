#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
int main() {
	cv::Mat src = cv::imread("/home/error/opencv practice/test/1_0.png", 1);
    cv::Mat gray,dst;  //用于绘制结果
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    threshold (gray,dst,127,255,THRESH_BINARY);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(dst, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);  //只找最外层轮廓

	std::vector<cv::RotatedRect> minAreaRects(contours.size());  //存储轮廓的最小外接矩形
	std::vector<cv::Rect> boundingRect(contours.size());  //存储轮廓的最小外接长方形

	cv::Point2f ps[4];  //外接矩形四个端点的集合
	for (int i = 0; i < contours.size(); ++i) {  //遍历所有轮廓
		minAreaRects[i] = cv::minAreaRect(contours[i]);  //获取轮廓的最小外接矩形
		minAreaRects[i].points(ps);  //将最小外接矩形的四个端点复制给rect数组

		for (int j = 0; j < 4; j++) {  //绘制最小外接轮廓的四条边
			line(dst, cv::Point(ps[j]), cv::Point(ps[(j + 1) % 4]), cv::Scalar(0, 255, 0), 8);
		}

		boundingRect[i] = cv::boundingRect(contours[i]);  //获取轮廓的最小外接长方形
		cv::rectangle(dst, boundingRect[i], cv::Scalar(255, 0, 0), 2);  //绘制最小外接长方形
	}

	cv::imshow("dst", dst);
	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}
