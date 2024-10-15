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
    // Print OpenCV version
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // Read image
    Mat image = imread("../shapes.jpg", IMREAD_GRAYSCALE);
    imshow("Original", image);

    // blur image
    Mat imageBlur;
    GaussianBlur(image, imageBlur, Size(5, 5), 0);
    imshow("Blur", imageBlur);

    // threshold image
    Mat imageThreshold;
    threshold(imageBlur, imageThreshold, 60, 255, THRESH_BINARY);
    imshow("threshold", imageThreshold);

    // find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imageThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // draw contours
    Mat imageContoursDraw;
    cvtColor(imageThreshold, imageContoursDraw, COLOR_GRAY2BGR);
    drawContours(imageContoursDraw, contours, -1, Scalar(0, 0, 255), 2);
    imshow("Contours", imageContoursDraw);

    // find triangles
    int count = 0;
    vector<Point> approx;

    for (unsigned int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

        // Skip small or non-convex objects
        if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;

        if (approx.size() >= 3 && approx.size() <= 6)
        {
            switch (approx.size())
            {
            case 4:
                count++;
                break;
            }
        }
    }

    // Print number of triangles
    cout << "Number of triangles: " << count << endl;

    // put text on the image
    putText(imageContoursDraw, "Num@ber of triangles: " + to_string(count), Point(10, 10), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 255, 255), 1, 8);

    // Show the image
    imshow("Triangles", imageContoursDraw);

    // Print number of squares found
    cout << "Number of squares: " << count << endl;


    // Close all windows
    waitKey();
    destroyAllWindows();

    return 0;
}