//Include Libraries
#include <opencv2/opencv.hpp>


// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;
void open();
void close();
Mat structCross, img_original, img_Dilate, img_Erode, img_open, img_close,tmp;

int main()
{
    structCross = getStructuringElement(MORPH_CROSS,Size(3,3)); //设定内核
    img_original = imread("/home/error/opencv practice/erodeandDilate/Hello World.png", 0);

    dilate(img_original,img_Dilate,structCross); //膨胀算法
    erode(img_original, img_Erode,structCross); //腐蚀算法
    open();
    close();

    imshow("original", img_original);
    imshow("Dilated",img_Dilate);
    imshow("Erode",img_Erode);
    imshow("open",img_open);
    imshow("close",img_close);

    waitKey(0);
    destroyAllWindows();
    imwrite("original.jpg", img_original);
    imwrite("Dilated.jpg",img_Dilate);
    imwrite("Erode.jpg",img_Erode);
    imwrite("open.jpg",img_open);
    imwrite("close.jpg",img_close);
}

void close()
{
    dilate(img_original,tmp,structCross);
    erode(tmp,img_close,structCross);
}

void open()
{
    erode(img_original,tmp,structCross);
    dilate(tmp,img_open,structCross);
}
