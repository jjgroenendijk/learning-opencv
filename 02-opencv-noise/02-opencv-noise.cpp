/*

Write a C-program that makes a snapshot with the camera and add some
“Gaussian noise” and do the same again and add some “salt and pepper
noise”. Show each time the original and the edited image.

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

    // Take a snapshot with the camera
    VideoCapture cap(1);

    // Check if the camera was opened successfully
    if (!cap.isOpened())
    {
        cout << "Error opening camera!" << endl;
        return -1;
    }

    // Create a Mat object to store the frame
    Mat frame;
    cap >> frame;

    // Check if the frame was captured successfully
    if (frame.empty())
    {
        cout << "Error: captured frame is empty!" << endl;
        return -1;
    }

    // Show the original image
    imshow("Original Image", frame);

    // Add Gaussian noise
    Mat gaussianNoise = frame.clone();
    randn(gaussianNoise, 0, 25);
    add(frame, gaussianNoise, gaussianNoise);

    // Show the image with Gaussian noise
    imshow("Gaussian Noise", gaussianNoise);


    // Create a grayscale image
    Mat grayImage;
    cvtColor(frame, grayImage, COLOR_BGR2GRAY);

    // Add salt and pepper noise
    Mat saltAndPepperNoise = grayImage.clone();

    // Generate random values between 0 and 255 in the matrix saltAndPepperNoise. The purpose is to create random noise to simulate the salt and pepper effect.
    randu(saltAndPepperNoise, 0, 255);

    // Turn pixel values lower than 10 into 0 (black) and others into 255 (white), resulting in a "salt" effect.
    threshold(saltAndPepperNoise, saltAndPepperNoise, 10, 255, THRESH_BINARY);

    // Turn pixel values higher than 245 into 0 (black) and others into 255 (white), resulting in a "pepper" effect.
    threshold(saltAndPepperNoise, saltAndPepperNoise, 245, 255, THRESH_BINARY_INV);

    // Add the salt and pepper noise to the original image
    add(grayImage, saltAndPepperNoise, saltAndPepperNoise);

    // Show the image with salt and pepper noise
    imshow("Salt and Pepper Noise", saltAndPepperNoise);

    // Wait for a key press
    waitKey(0);

    return 0;
}