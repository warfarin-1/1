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

class light_blob
{
private:
    float x;
    float y;
    int layer;
public:
    void input_x(float m_x){
        x=m_x;
    }
    void input_y(float m_y){
        y=m_y;
    }
    void input_layer(int m_layer){
        layer=m_layer;
    }
    float output_x(){
        return x;
    }
    float output_y(){
        return y;
    }
    int output_layer(){
        return layer;
    }
};

int main(){
    Mat src, color_channel, src_bin_light_0, src_bin_light, img_GaussianBlur,dst;
    int photo_num, i, j;
    float aspectRatio, distance, point_x, point_y, width, height;
    light_blob arr[32];
    vector<vector<Point>> light_contours;
    vector<Vec4i> hierarchy_light;

    src = imread("/home/error/opencv practice/light-blob/red_light.png",1);
    dst=src;
//    imshow("original",src);

    vector<Mat> channels;       // 通道拆分
    split(src, channels);
    color_channel = channels[2] - channels[0] / 2 - channels[1] / 2;
//    imshow("channels",color_channel);
    threshold (color_channel,src_bin_light_0,143,255,THRESH_BINARY);//二值化
//    imshow("srcBinLight_0",src_bin_light_0);
    GaussianBlur(src_bin_light_0,img_GaussianBlur,Size(9,9),2,2);// 高斯滤波
//    imshow("GaussianBlur",img_GaussianBlur);
    imagePreProcess(img_GaussianBlur,src_bin_light);//开闭运算
//    imshow("src_bin_light",src_bin_light);


    findContours(src_bin_light,light_contours,hierarchy_light,RETR_EXTERNAL,CHAIN_APPROX_NONE); //查找轮廓
    vector<RotatedRect> minAreaRects(light_contours.size());
    vector<Rect> boundingRect(light_contours.size());
    photo_num=0;
    for (i = 0; i < light_contours.size(); i++) //遍历所有轮廓
    {
        RotatedRect rect1=minAreaRect(light_contours[i]);
        boundingRect[i] = cv::boundingRect(light_contours[i]);  //获取轮廓的最小外接长方形
        aspectRatio = (float)boundingRect[i].width /(float)boundingRect[i].height; //计算轮廓长宽比
        if(aspectRatio > 0.25 && aspectRatio < 0.75) //存储灯条
        {
            arr[photo_num].input_x(rect1.center.x);
            arr[photo_num].input_y(rect1.center.y);
            arr[photo_num].input_layer(i);
            rectangle(dst, boundingRect[i], Scalar(255, 0, 0), 2);  //绘制最小外接长方形
            photo_num++;
        }
    }
    for(i = 0; i < photo_num; i++)
    {
        for(j= i+1; j < photo_num; j++)
        {
            distance = sqrt(pow(arr[i].output_x() - arr[j].output_x(),2)
                    + pow(arr[i].output_y() - arr[j].output_y(),2));
            if(distance < 100 && distance > 50)
            {
                if(arr[i].output_x()<arr[j].output_x())
                {
                    point_x= arr[i].output_x() *1.04;
                }
                else
                {
                    point_x= arr[j].output_x() *1.04;
                }
                width = fabs(arr[i].output_x() - arr[j].output_x()) * 0.72;
                height = (boundingRect[arr[i].output_layer() ].height + boundingRect[arr[j].output_layer()].height) / 1.7;
                point_y= (arr[i].output_y()+arr[j].output_y()) / 2 - height / 2;
                Rect r1(point_x, point_y, width, height);
                rectangle(dst, r1, Scalar(0, 255, 0), 2, 8, 0);
            }
        }
    }
    imshow("dst",dst);
    waitKey(0);
    return 0;
}