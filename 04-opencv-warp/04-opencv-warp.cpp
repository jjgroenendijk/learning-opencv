/*

Write a C-program (using OpenCV functions) that takes the license plat from the
above image and puts it into a new image using the warp function.

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

    // check if the image was opened successfully
    if (image.empty())
    {
        cout << "Error opening image!" << endl;
        return -1;
    }

    /*

        Explanation:

        The warp function is used to apply a geometric transformation to an image.

    */

    // Create a new image
    Mat warped_image;

    // Define the points of the license plate
    vector<Point2f> srcPoints;
    srcPoints.push_back(Point2f(30, 65));                               // top-left
    srcPoints.push_back(Point2f((image.cols - 20), 10));                // top-right
    srcPoints.push_back(Point2f((image.cols - 25), (image.rows - 70))); // bottom-right
    srcPoints.push_back(Point2f(15, image.rows));                       // bottom-left

    // Define the points of the new image. Use the original resolution
    vector<Point2f> dstPoints;
    dstPoints.push_back(Point2f(0, 0));
    dstPoints.push_back(Point2f(image.cols, 0));
    dstPoints.push_back(Point2f(image.cols, image.rows));
    dstPoints.push_back(Point2f(0, image.rows));

    // Create the transformation matrix
    Mat transformationMatrix = getPerspectiveTransform(srcPoints, dstPoints);

    // Apply the transformation
    warpPerspective(image, warped_image, transformationMatrix, image.size());

    // Show the original image
    imshow("Original Image", image);

    // Show the warped image
    imshow("Warped Image", warped_image);

    // Wait for a key press
    waitKey(0);

    return 0;
}