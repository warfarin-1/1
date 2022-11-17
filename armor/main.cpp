#include <opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

void imagePreProcess(Mat & src0, Mat & src1)
{
    static Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(src0, src1, kernel_erode);

    static Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(src1, src1, kernel_dilate);

    static Mat kernel_dilate2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(src1, src1, kernel_dilate2);

    static Mat kernel_erode2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(src1, src1, kernel_erode2);
}

int main(){
    Mat src, color_channel, src_bin_light_0, src_bin_light, img_GaussianBlur,dst;
    int photo_num, i, j, k;
    float angle, check_area, width, height;
    vector<vector<Point>> light_contours;
    vector<Vec4i> hierarchy_light;
    Point2f point[1];

    src = imread("/home/error/opencv practice/armor/red_light.png",1);
    dst = src;
    imshow("original",src);

    vector<Mat> channels;       // 通道拆分
    split(src, channels);
    color_channel = channels[2] - channels[0] / 2 - channels[1] / 2;
//    imshow("channels",color_channel);
    threshold (color_channel,src_bin_light_0,127,255,THRESH_BINARY);//二值化
//    imshow("srcBinLight_0",src_bin_light_0);
    GaussianBlur(src_bin_light_0,img_GaussianBlur,Size(9,9),2,2);// 高斯滤波
//    imshow("GaussianBlur",img_GaussianBlur);
    imagePreProcess(img_GaussianBlur,src_bin_light);//开闭运算
//    imshow("src_bin_light",src_bin_light);


    findContours(src_bin_light,light_contours,hierarchy_light,RETR_EXTERNAL,CHAIN_APPROX_NONE); //查找轮廓
    vector<RotatedRect> minAreaRects(light_contours.size());  //存储轮廓的最小外接矩形
    Point2f ps[4];  //外接矩形四个端点的集合
    for (i = 0; i < light_contours.size(); ++i) {  //遍历所有轮廓
        minAreaRects[i] = minAreaRect(light_contours[i]);  //获取轮廓的最小外接矩形
        photo_num = i;
    }

    for(i = 0; i < photo_num; i++)
    {
        if(minAreaRects[i].size.aspectRatio() > 1.8 || minAreaRects[i].size.aspectRatio() < 0.3) continue;
        else {
            for (j = i + 1; j < photo_num; j++) {
                if(minAreaRects[j].size.aspectRatio() > 1.8 || minAreaRects[j].size.aspectRatio() < 0.3) continue;
                else {
                    check_area = abs(minAreaRects[i].size.area() - minAreaRects[j].size.area()) /
                                 ((minAreaRects[i].size.area() + minAreaRects[j].size.area()) / 2);
                    if (check_area < 0.1) {
                        minAreaRects[i].points(ps);  //将最小外接矩形的四个端点复制给ps数组
                        for (k = 0; k < 4; k++) {  //绘制最小外接轮廓的四条边
                            line(dst, Point(ps[k]), Point(ps[(k + 1) % 4]), Scalar(0, 255, 0), 2);
                        }
                        minAreaRects[j].points(ps);  //将最小外接矩形的四个端点复制给ps数组
                        for (k = 0; k < 4; k++) {  //绘制最小外接轮廓的四条边
                            line(dst, Point(ps[k]), Point(ps[(k + 1) % 4]), Scalar(0, 255, 0), 2);
                        }
                        angle = (minAreaRects[i].angle + minAreaRects[j].angle) / 2;
                        point[0] = (minAreaRects[i].center + minAreaRects[j].center) / 2;
                        width = (minAreaRects[i].size.width + minAreaRects[j].size.width) / 1.5;
                        height = (minAreaRects[i].size.height + minAreaRects[j].size.height);
                        RotatedRect r1;
                        r1.center = point[0];
                        r1.angle = angle;
                        r1.size = {width,height};
                        Point2f vertices[4];
                        r1.points(vertices);
                        for (int k = 0; k < 4; k++)
                        {
                            line(dst, vertices[k], vertices[(k + 1) % 4], Scalar(255, 255, 0),4);
                        }
                    }
                }
            }
        }
    }
    imshow("dst",dst);
    waitKey(0);
    return 0;
}
