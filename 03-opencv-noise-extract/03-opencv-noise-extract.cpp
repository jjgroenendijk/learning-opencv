/*

Write a C-program (using OpenCV functions) that will extract the noise as
much as possible from the above image. Show again the original and the ed-
ited image on the screen.

*/

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

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
    if (image.empty())
    {
        cout << "Error opening image!" << endl;
        return -1;
    }

    // Show the original image
    imshow("Original Image", image);

    /*
    
        Filters are used to reduce the perceived noise in an image.
        There are several filters available in OpenCV to denoise an image.
        Here we use the following filters:
            Gaussian Blur
            Median Blur
            Bilateral Filter
    
    */

    // Gaussian Blur
    Mat denoiseGaussianBlur;
    GaussianBlur(image, denoiseGaussianBlur, Size(7, 7), 1.5);
    imshow("Denoised Image with Gaussian blur", denoiseGaussianBlur);

    // Median Blur
    Mat denoiseMedianBlur;
    medianBlur(image, denoiseMedianBlur, 5);
    imshow("Denoised Image with Median blur", denoiseMedianBlur);

    // Bilateral Filter
    Mat denoiseBilateralFilter;
    bilateralFilter(image, denoiseBilateralFilter, 9, 75, 75);
    imshow("Denoised Image with Bilateral Filter", denoiseBilateralFilter);

    // Wait for a key press
    waitKey(0);

    return 0;
}