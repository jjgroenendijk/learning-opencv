#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // Read image
    Mat src = imread("carpet.bmp",IMREAD_GRAYSCALE);
    imshow("Original carpet", src);

    // Create gaussian kernel

    Mat filter, filter2, filter3 = src.clone();
    GaussianBlur(src, filter, Size(5,5), 0);
    GaussianBlur(src, filter2, Size(15,15), 0);
    GaussianBlur(filter, filter3, Size(17,17),7);

    // Show the Filter image
    imshow("Filter image", filter);
    imshow("Filter image 2", filter2);
    imshow("Filter image 3", filter3);


    // Create a new image as a black rectangle
    Mat customRectangle = Mat::zeros(200,200,CV_8U);
    rectangle(customRectangle,Point(50,50),Point(150,150),Scalar(255),FILLED);
    imshow("Source image",customRectangle);

    // Smooth the image with a 5x5 gaussian filter
    Mat customRectangleFilter1, customRectangleFilter2, customRectangleFilter3 = customRectangle.clone();
    GaussianBlur(customRectangle, customRectangleFilter1, Size(5,5), 0);
    GaussianBlur(customRectangle, customRectangleFilter2, Size(15,15), 0);
    GaussianBlur(customRectangleFilter1, customRectangleFilter3, Size(5,5), 0);
    imshow("Dst1 image",customRectangleFilter1);
    imshow("Dst2 image",customRectangleFilter2);
    imshow("Dst3 image",customRectangleFilter3);

    waitKey(0);
    destroyAllWindows();
    return 0;
}