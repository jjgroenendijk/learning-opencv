#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    cout << "OpenCV Version: " << CV_VERSION << endl;

    /*
    
        01. Ballbar.bmp
            Use morphology functions to disassemble the ball and the bar. Make 2 new pictures one with the ball and one with the bar.
    
    */

    // Read the image
    Mat ballbarOriginal = imread("ballbar.bmp");
    imshow("Original image",ballbarOriginal);

    // Create a binary image
    Mat ballbarBinary = ballbarOriginal.clone();
    cvtColor(ballbarOriginal, ballbarBinary, COLOR_BGR2GRAY);
    threshold(ballbarBinary, ballbarBinary, 127, 255, THRESH_BINARY_INV);
    imshow("Binary image", ballbarBinary);

    // Morphology
    Mat ballbarMorph = ballbarBinary.clone();
    Mat kernelEllipse = getStructuringElement(MORPH_ELLIPSE, Size(15,15));
    morphologyEx(ballbarBinary, ballbarMorph, MORPH_OPEN, kernelEllipse);
    imshow("Ballbar Morph", ballbarMorph);

    // Result
    Mat ballbarResult = ballbarBinary - ballbarMorph;
    imshow("Morph result", ballbarResult);

    // Inverted result
    Mat ballbarResultInv = ballbarResult.clone();
    bitwise_not(ballbarResult, ballbarResultInv);
    imshow("Inverted morph result", ballbarResultInv);

    /*
    
        02. bars.bmp
            Use morphology functions to disassemble the vertical bar and
            the horizontal lines. Make 2 new pictures, one with the vertical
            bar and one with the horizontal lines (these must not be inter-
            rupted).

    */

    // Read the image
    Mat barsOriginal = imread("bars.bmp");
    imshow("Original bars", barsOriginal);

    // Create a binary image
    Mat barsBinary = barsOriginal.clone();
    cvtColor(barsOriginal, barsBinary, COLOR_BGR2GRAY);
    threshold(barsBinary, barsBinary, 127, 255, THRESH_BINARY_INV);
    imshow("Binary bars", barsBinary);

    // Morphology
    int kdata1[] = {1,1,1,1,1};
    Mat kernel1 (5,1,CV_8U,kdata1);
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(19,1));

    Mat barsMorph1 = barsBinary.clone();
    morphologyEx(barsBinary, barsMorph1, MORPH_OPEN, kernel1);
    imshow("Morph bars", barsMorph1);

    Mat barsMorph2 = barsBinary.clone();
    morphologyEx(barsBinary, barsMorph2, MORPH_OPEN, kernel2);
    imshow("Morph bars 2", barsMorph2);

    /*
    
        03. ballstripes.bmp
            Use morphology functions to remove the stripes from the image
            to create a new image with only balls.
    
    */

    // Read the image
    Mat ballstripesOriginal = imread("ballstripes.bmp");
    imshow("Original ballstripes", ballstripesOriginal);

    // Create a binary image
    Mat ballstripesBinary = ballstripesOriginal.clone();
    cvtColor(ballstripesOriginal, ballstripesBinary, COLOR_BGR2GRAY);
    threshold(ballstripesBinary, ballstripesBinary, 127, 255, THRESH_BINARY_INV);
    imshow("Binary ballstripes", ballstripesBinary);

    // Morphology
    Mat ballstripesMorph = ballstripesBinary.clone();
    int kernelData[] = {1,1,1,1,1,1,1,1,1};
    Mat kernel (5,5,CV_8U,kernelData);
    morphologyEx(ballstripesBinary, ballstripesMorph, MORPH_OPEN, kernel);
    imshow("Morph ballstripes", ballstripesMorph);

    // Different method
    Mat kernelBalls = getStructuringElement(MORPH_ELLIPSE, Size(10,10));
    morphologyEx(ballstripesBinary, ballstripesMorph, MORPH_OPEN, kernelBalls);
    imshow("Morph ballstripes 2", ballstripesMorph);

    // Result
    bitwise_not(ballstripesMorph, ballstripesMorph);
    imshow("Morph result ballstripes", ballstripesMorph);

    /*
    
        04. gear.bmp
            Use morphology functions to remove the gear from the image to
            create a new image with only the background.
    
    */

    // Read the image
    Mat gearOriginal = imread("gear.bmp");
    imshow("Original gear", gearOriginal);

    // Create a binary image
    Mat gearBinary = gearOriginal.clone();
    cvtColor(gearOriginal, gearBinary, COLOR_BGR2GRAY);
    threshold(gearBinary, gearBinary, 127, 255, THRESH_BINARY);
    imshow("Binary gear", gearBinary);

    // Morphology
    

    waitKey(0);

    destroyAllWindows();

    return 0;
}