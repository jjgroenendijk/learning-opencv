/*

    Write a C-program (using OpenCV functions) that can find all the words 'programma' from the image and puts a rectangle around the locations found.

*/

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    double minV, maxV;
    Point minL, maxL;
    Mat MatchingSpace;
    Mat work;

    // Print OpenCV version
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // Read image from file
    Mat image = imread("../Text.jpg");

    // Show the Original image
    imshow("Original image", image);

    // Place and size of 'programma'
    int x = 70, y = 50, width = 113, height = 24;

    // Create template
    Rect roi_rect(x, y, width, height);
    Mat roi = image(roi_rect);
    imshow("ROI", roi);

    work = image.clone();

    while (true)
    {
        MatchingSpace.create(image.cols - (roi.cols + 1), image.rows - (roi.rows + 1), CV_32F);
        matchTemplate(work, roi, MatchingSpace, TM_CCOEFF_NORMED);
        minMaxLoc(MatchingSpace, &minV, &maxV, &minL, &maxL);

        if (maxV >= 0.53)
        {
            // set rectangle around 'programma'
            rectangle(image, maxL, Point(maxL.x + roi.cols, maxL.y + roi.rows), Scalar::all(0), 1, 8, 0);

            // remove 'programma' from search (work) image
            rectangle(work, maxL, Point(maxL.x + roi.cols, maxL.y + roi.rows), Scalar::all(0), FILLED);
        }
        else
        {
            break;
        }
    }
    // Show Result and work image
    imshow("Work", work);
    moveWindow("Work", 350, 100);

    imshow("Result", image);

    // Close all windows
    if (waitKey(0) == 27)
    {
        destroyAllWindows();
    }

    return 0;
}