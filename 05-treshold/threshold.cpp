#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // check the number of arguments
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <image_path>" << endl;
        return -1;
    }

    // check if the file exists
    if (!std::__fs::filesystem::exists(argv[1]))
    {
        cout << "File not found: " << argv[1] << endl;
        return -1;
    }

    // read the image
    Mat image = imread(argv[1]);

    // check if the image was opened successfully
    if (image.empty())
    {
        cout << "Error opening image!" << endl;
        return -1;
    }

    /*
        Explanation:
        Tresholding is a technique used to separate the foreground from the background in an image.

        Types of SIMPLE tresholding:
        - THRESH_BINARY (if pixel value is greater than threshold, it is assigned the max value, otherwise 0)
        - THRESH_BINARY_INV (if pixel value is greater than threshold, it is assigned 0, otherwise the max value)
        - THRESH_TRUNC (if pixel value is greater than threshold, it is assigned the threshold value, otherwise the pixel value)
        - THRESH_TOZERO (if pixel value is greater than threshold, it is assigned the pixel value, otherwise 0)
        - THRESH_TOZERO_INV (if pixel value is greater than threshold, it is assigned 0, otherwise the pixel value)

        The thresholding function is defined as follows:
        void threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);

        Types of adaptive thresholding:
        - ADAPTIVE_THRESH_MEAN_C (threshold value is the mean of the neighbourhood area)
        - ADAPTIVE_THRESH_GAUSSIAN_C (threshold value is the weighted sum of the neighbourhood area)

        The adaptive thresholding function is defined as follows:
        void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C);

        Otsu's Binarization:
        - Automatically calculates the threshold value from the image histogram
        - The threshold value is the one that minimizes the intra-class variance
        - The function is defined as follows:

        double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);

        Example:
        threshold(src, dst, 127, 255, THRESH_BINARY, TREHS_OTSU);
    */

    // Convert the image to grayscale

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Apply thresholding
    Mat thresholdBinary, thresholdBinaryInv, thresholdTrunc, thresholdToZero, thresholdToZeroInv;
    Mat adaptiveThresholdMean, adaptiveThresholdGaussian;
    Mat thresholdOtsu;

    threshold(grayImage, thresholdBinary, 127, 255, THRESH_BINARY);
    threshold(grayImage, thresholdBinaryInv, 127, 255, THRESH_BINARY_INV);
    threshold(grayImage, thresholdTrunc, 127, 255, THRESH_TRUNC);
    threshold(grayImage, thresholdToZero, 127, 255, THRESH_TOZERO);
    threshold(grayImage, thresholdToZeroInv, 127, 255, THRESH_TOZERO_INV);

    adaptiveThreshold(grayImage, adaptiveThresholdMean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 15);
    adaptiveThreshold(grayImage, adaptiveThresholdGaussian, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 15);

    threshold(grayImage, thresholdOtsu, 240, 255, THRESH_BINARY | THRESH_OTSU);

    // Display the images
    imshow("Original Image", image);
    imshow("Gray Image", grayImage);
    imshow("Binary Threshold", thresholdBinary);
    imshow("Binary Inverted Threshold", thresholdBinaryInv);
    imshow("Truncated Threshold", thresholdTrunc);
    imshow("To Zero Threshold", thresholdToZero);
    imshow("To Zero Inverted Threshold", thresholdToZeroInv);
    imshow("Adaptive Threshold Mean", adaptiveThresholdMean);
    imshow("Adaptive Threshold Gaussian", adaptiveThresholdGaussian);
    imshow("Otsu's Threshold", thresholdOtsu);

    waitKey(0);

    return 0;
}