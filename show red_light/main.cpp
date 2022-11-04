//Include Libraries
#include <opencv2/opencv.hpp>
#include <vector>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;


int main() 
{
    Mat img_grayscale = imread("/home/error/opencv practice/test/RGB.png", 1);
    if(img_grayscale.empty())
    {
        cout << "No Image" << endl;
        return -1;
    }
    Mat light_channel;
    vector<Mat> channels;
    split(img_grayscale, channels);
    light_channel= channels[2]-channels[0]/2-channels[1]/2;
    imshow("original",img_grayscale);
    imshow ("channel_0",channels[0]);
    imshow ("channel_1",channels[1]);
    imshow ("channel_2",channels[2]);
    imshow("light_channel",light_channel);
    
    waitKey(0);
    destroyAllWindows();
    //imwrite ("",);
}
