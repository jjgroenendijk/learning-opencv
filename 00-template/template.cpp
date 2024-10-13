/*

    Template for OpenCV C++ programs
    Close windows with ESC key
    Make sure images are located in build folder
    cmakelists.txt should be in the same folder as the source code

*/

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{

    cout << "OpenCV Version: " << CV_VERSION << endl;

    // Read image
    Mat image = imread("ballbar.bmp", IMREAD_GRAYSCALE);

    // Create trackbars for fast value selection
    namedWindow("Window Title Here");
    int valueX = 0;
    int valueXMax = 255;
    int valueY = 0;
    int valueYMax = 255;
    createTrackbar("Value X", "Window Title Here", &valueX, valueXMax);
    createTrackbar("Value Y", "Window Title Here", &valueY, valueYMax);

    Mat destination;

    while (true)
    {
        // Apply thingies here, using the trackbar values
        threshold(image, destination, valueX, valueY, THRESH_BINARY_INV);

        // Show the image
        imshow("Window Title Here", destination);

        // Press ESC to close the window
        if (waitKey(30) == 27)
        {
            break;
        }
    }

    // Print the optimal values
    cout << "Optimal value X:" << valueX << endl;
    cout << "Optimal value Y:" << valueY << endl;

    // Close all windows
    destroyAllWindows();

    return 0;
}