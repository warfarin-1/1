//Include Libraries
#include<opencv2/opencv.hpp>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;


int main() {
    Mat img_grayscale = imread("/home/error/opencv practice/splitchannels/01.jpeg", 1);
    vector<Mat> channels;

    split(img_grayscale, channels);
    Mat B,G,R;
    //imshow("grayscale image", img_grayscale); //图片显示

    /*imshow("Blue Channel", channels[0]);//三通道灰度图的分离
    imshow("Green Channel", channels[1]);
    imshow("Red Channel", channels[2]);*/

    channels[1] = 0;
    channels[2] = 0;
    merge(channels, B);
    imshow("Blue Channel", B);

    split(img_grayscale, channels);
    channels[0] = 0;
    channels[2] = 0;
    merge(channels, G);
    imshow("Green Channel", G);

    split(img_grayscale, channels);
    channels[0] = 0;
    channels[1] = 0;
    merge(channels, R);
    imshow("Red Channel", R);



    waitKey(0);

    destroyAllWindows();

    //imwrite("Akie.jpg", img_grayscale);
    imwrite("B.jpg", B);
    imwrite("G.jpg", G);
    imwrite("R.jpg", R);
}
