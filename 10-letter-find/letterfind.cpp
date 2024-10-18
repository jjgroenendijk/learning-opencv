/*

    Template for OpenCV C++ programs
    Close windows with ESC key
    Make sure images are located in build folder
    cmakelists.txt should be in the same folder as the src code

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

    // Create Mat objects
    double minV, maxV;
    Point minL, maxL;
    Mat MatchingSpace;
    Mat src;
    Mat work;

    // read image
    src = imread("../Tekst.bmp", IMREAD_GRAYSCALE);

    // check if image is loaded
    if (src.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Show the Original image
    imshow("Original image", src);

    /* Place and size of 'L' */
    int x = 147, y = 21, width = 12, height = 14;
    /* Create template */
    Rect roi_rect(x, y, width, height);
    Mat roi = src(roi_rect);
    imshow("ROI", roi);

    work = src.clone();

    while (true)
    {
        MatchingSpace.create(src.cols - (roi.cols + 1), src.rows - (roi.rows + 1), CV_32F);
        matchTemplate(work, roi, MatchingSpace, TM_CCOEFF_NORMED);
        minMaxLoc(MatchingSpace, &minV, &maxV, &minL, &maxL);

        if (maxV >= 0.53)
        {
            // set rectangle arounf letter 'L'
            rectangle(src, maxL, Point(maxL.x + roi.cols, maxL.y + roi.rows), Scalar::all(0), 1, 8, 0);
            // remove letter 'L' from search (work) image
            rectangle(work, maxL, Point(maxL.x + roi.cols, maxL.y + roi.rows), Scalar::all(0), FILLED);
        }
        else
        {
            break; /* no match anymore, stop searching */
        }
    }
    // Show Result and work image
    imshow("Work", work);
    moveWindow("Work", 350, 100);

    imshow("Result", src);

    // End
    waitKey(0);
    destroyAllWindows();

    return 0;
}