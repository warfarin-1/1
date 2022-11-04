//Include Libraries
#include <opencv2/opencv.hpp>
#include <vector>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;
Mat img_grayscale,img_resize,img_GaussianBlur,img_threshold,img_contours;
int i;

int main() {
    img_grayscale = imread("/home/error/opencv practice/contours/01.jpeg", 0);
    if(img_grayscale.empty())
    {
        cout << "No Image" << endl;
        return -1;
    }
    //imshow("original",img_grayscale);

    resize(img_grayscale,img_resize, Size(), 0.5, 0.5, INTER_LINEAR);// 缩放至0.5倍
    //imshow("resize",img_resize);

    GaussianBlur(img_resize,img_GaussianBlur,Size(9,9),2,2);// 高斯滤波
    threshold (img_GaussianBlur,img_threshold,160,255,THRESH_BINARY);

    vector<vector<Point>>contours; //这两行不知道怎么用
    vector<Vec4i>hierarchy;
    findContours(img_threshold,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE); //查找轮廓
    img_contours =img_resize;
    drawContours(img_contours,contours,-1,Scalar(0,0,255),1,8);//绘制轮廓
    for(i=0;i<hierarchy.size();++i)
    {
        cout << hierarchy[i] << endl;
    }

    //imshow("gaussianblur",img_GaussianBlur);
    //imshow("threshold",img_threshold);
    imshow("contours",img_contours);

    /*imwrite("original.jpg",img_grayscale);
    imwrite("resize.jpg",img_resize);
    imwrite("gaussianblur.jpg",img_GaussianBlur);
    imwrite("threshold.jpg",img_threshold);
    imwrite("contours.jpg",img_contours);*/

    waitKey(0);
    destroyAllWindows();
    //imwrite("",);
}