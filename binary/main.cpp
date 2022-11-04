//Include Libraries
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;


int main() {
    Mat img_grayscale = imread("/home/error/opencv practice/binary/01.jpeg", 0);
    Mat final;
    threshold (img_grayscale,final,127,255,THRESH_BINARY); //二值化
    //medianBlur(img_grayscale,final,17);
    imshow("final",final);

    waitKey(0);
    destroyAllWindows();

    imwrite("binary.jpg",final);
}
