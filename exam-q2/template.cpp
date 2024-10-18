/*

    Use morphology functions to seperate the line and the balls in the image.
    Write a program (using OpenCV) that is creating result 1 and result 2 out of the original image.

*/

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    // Print OpenCV version
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // Read image from file
    Mat image = imread("../StripBalls.jpg");

    // Check if image is loaded
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    
    // Show the Original image
    imshow("Original image", image);

    // Convert to grayscale
    Mat image_gray;
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    imshow("Grayscale image", image_gray);

    // Threshold
    Mat image_binary;
    threshold(image_gray, image_binary, 127, 255, THRESH_BINARY_INV);

    // Morphology for balls
    Mat balls = image_binary.clone();
    Mat kernelBalls = getStructuringElement(MORPH_ELLIPSE, Size(60,60));
    morphologyEx(image_binary, balls, MORPH_OPEN, kernelBalls);

    // Invert image 
    Mat balls_inv = balls.clone();
    bitwise_not(balls, balls_inv);
    imshow("Result 2 - Balls", balls_inv);
    
    // Subtract balls from original image
    Mat bar = image.clone();
    bar.setTo(Scalar(255,255,255), balls);

    // Define a simple kernel
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));

    // Remove noise from bar
    morphologyEx(bar, bar, MORPH_CLOSE, kernel);

    // Show the Result image
    imshow("Result 1 - Bar", bar);

    // Press ESC to close the windows
    if (waitKey(0) == 27)
    {
        destroyAllWindows();
    }

    return 0;
}