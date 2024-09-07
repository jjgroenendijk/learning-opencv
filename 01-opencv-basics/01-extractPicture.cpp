/*

Write a C-program (using OpenCV functions) that reads the above RGB image
and converts it to 3 gray value images, 1 for Red, 1 for Green and 1 for Blue
values.

b. Convert the RGB image to an HSV image and show the Hue, Saturation and
Value as gray value images.

*/

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main (int argc, char **argv) {

    cout << "OpenCV Version: " << CV_VERSION << endl;

    // check the number of arguments
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <image_path>" << endl;
        return -1;
    }

    // check if the file exists
    if (! std::__fs::filesystem::exists(argv[1])) {
        cout << "File not found: " << argv[1] << endl;
        return -1;
    }
    else {
        cout << "File found: " << argv[1] << endl;
    }

    // read the image
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Error opening image!" << endl;
        return -1;
    }

// Split into Red, Green, and Blue channels
    vector<Mat> rgbChannels(3);
    split(image, rgbChannels);

    // Display Red, Green, and Blue channels as grayscale images
    imshow("Red Channel", rgbChannels[2]);
    imshow("Green Channel", rgbChannels[1]);
    imshow("Blue Channel", rgbChannels[0]);

    // Convert RGB to HSV
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // Split into Hue, Saturation, and Value channels
    vector<Mat> hsvChannels(3);
    split(hsvImage, hsvChannels);

    // Display Hue, Saturation, and Value as grayscale images
    imshow("Hue Channel", hsvChannels[0]);
    imshow("Saturation Channel", hsvChannels[1]);
    imshow("Value Channel", hsvChannels[2]);

    waitKey(0);


    return 0;

}