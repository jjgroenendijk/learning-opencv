#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*

    Write a C-program that removes the cells from
    the picture, using edge detection, and puts
    them into a new image with also the number of
    found cells

*/

int main(int argc, char **argv)
{
    cout << "OpenCV Version: " << CV_VERSION << endl;
    cout << "Press ESC to close OpenCV windows" << endl;

    // Read image
    Mat img = imread("shading_c.bmp", IMREAD_GRAYSCALE);
    imshow("Original image", img);

    // create trackbars for Canny edge detection
    namedWindow("Canny");
    int lowThreshold = 0;
    int highThreshold = 100;
    createTrackbar("Low Threshold", "Canny", &lowThreshold, 100);
    createTrackbar("High Threshold", "Canny", &highThreshold, 255);

    int cells = 0;
    Mat ndst;

    while (true)
    {
        Mat edges;
        Canny(img, edges, lowThreshold, highThreshold);

        cells = connectedComponents(edges, ndst, 8);

        imshow("Canny", edges);

        if (waitKey(30) == 27)
            break;
    }

    // Destroy windows and print number of cells
    destroyAllWindows();
    cout << "Number of cells: " << cells - 1 << endl;

    Mat imgConnectedBalls = imread("connectedballs.bmp", IMREAD_GRAYSCALE);
    imshow("Connected balls", imgConnectedBalls);

    Mat thresholded;
    threshold(imgConnectedBalls, thresholded, 100, 255, THRESH_BINARY_INV);
    imshow("Thresholded", thresholded);

    Mat distanceTransformed;
    distanceTransform(thresholded, distanceTransformed, DIST_L1, 3);

    normalize(distanceTransformed, distanceTransformed, 0, 255, NORM_MINMAX, CV_8U);

    imshow("Distance transformed", distanceTransformed);

    Mat thresholded2;

    threshold(distanceTransformed, thresholded2, 100, 255, THRESH_BINARY);

    imshow("Thresholded 2", thresholded2);

    Mat ndst2;

    int balls = connectedComponents(thresholded2, ndst2, 8);

    cout << "Number of balls: " << balls - 1 << endl;

    waitKey(0);
    destroyAllWindows();

    /*

        Circle detection with Hough circle transform

        Function: HoughCircles

        Parameters:
        - Input image
        - Output vector of circles
        - Detection method (only HOUGH_GRADIENT available)
        - Inverse ratio of the accumulator resolution to the image resolution
        - Minimum distance between the centers of the detected circles
        - Upper threshold for the internal Canny edge detector
        - Threshold for center detection
        - Minimum radius to detect
        - Maximum radius to detect

    */

    Mat coins = imread("coins.jpg", IMREAD_COLOR);
    Mat coinsGray;
    cvtColor(coins, coinsGray, COLOR_BGR2GRAY);
    GaussianBlur(coinsGray, coinsGray, Size(9, 9), 2, 2);

    vector<Vec3f> circles;

    HoughCircles(coinsGray, circles, HOUGH_GRADIENT, 1, coinsGray.rows / 8, 200, 100, 0, 0);

    // Loop over all circles
    for (size_t i = 0; i < circles.size(); i++)
    {
        // Show which circle is being drawn
        cout << "Circle " << i << ": " << circles[i] << endl;

        // Get center point of circle
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        
        // Get radius of circle
        int radius = cvRound(circles[i][2]);

        // Draw middle point of circle
        circle(coins, center, 3, Scalar(0, 255, 0), -1, 8, 0);

        // Draw circle
        circle(coins, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }

    imshow("Coins", coins);

    waitKey(0);
    destroyAllWindows();

    return 0;
}