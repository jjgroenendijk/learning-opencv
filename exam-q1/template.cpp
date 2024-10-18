/*

    Write a program using OpenCV that count the number of yellow circles and show these number on the original image.

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
    Mat image = imread("../ColoredFigures.jpg");
    imshow("Image", image);

    // Apply smoothing to image
    Mat image_blur;
    GaussianBlur(image, image_blur, Size(5, 5), 0);

    // Convert image to HSV
    Mat image_hsv;
    cvtColor(image_blur, image_hsv, COLOR_BGR2HSV);

    // Mask image
    Mat image_mask_yellow;
    inRange(image_hsv, Scalar(10, 0, 0), Scalar(50, 255, 255), image_mask_yellow);
    imshow("Mask", image_mask_yellow);

    // Apply opening morph to image
    Mat image_morph;
    Mat kernelEllipse = getStructuringElement(MORPH_ELLIPSE, Size(40, 40));
    morphologyEx(image_mask_yellow, image_morph, MORPH_OPEN, kernelEllipse);
    imshow("Morph", image_morph);

    // Find circles in image
    vector<Vec3f> circles;
    HoughCircles(image_morph, circles, HOUGH_GRADIENT, 1, image_morph.rows / 8, 300, 20, 0, 0);

    // Loop over all circles
    for (size_t i = 0; i < circles.size(); i++)
    {
        // Show which circle is being drawn
        cout << "Circle " << i << ": " << circles[i] << endl;

        // Get center point of circle
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

        // Get radius of circle
        int radius = cvRound(circles[i][2]);

        // Draw circle
        circle(image, center, radius, Scalar(0, 0, 255), 8, 8, 0);
    }

    // Print the amount of circles found
    cout << "Number of yellow circles: " << circles.size() << endl;

    // Put text on the image with the amount of circles found
    putText(image, "Yellow circles: " + to_string(circles.size()), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    imshow("Yellow circles", image);

    // Press ESC to close the window
    if (waitKey(0) == 27)
    {
        destroyAllWindows();
    }
}