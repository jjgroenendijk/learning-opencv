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
    Mat frame;
    Mat src;

    // Print OpenCV version
    cout << "OpenCV Version: " << CV_VERSION << endl;

    // read video
    VideoCapture video("../dices.mp4");

    // Set up blob detector
    SimpleBlobDetector::Params params;

    // Delete black areas smaller than 40 pixels or bigger than 100 pixels
    params.filterByArea = true;
    params.minArea = 40;
    params.maxArea = 100;

    // Only accept BLOBs with a black color (Frames are thresholded so it is 0 or 255)
    params.filterByColor = true;
    params.blobColor = 0;

    // Only accept circular shapes
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    params.maxThreshold = 255;
    params.minThreshold = 210;

    // Create BLOB detector
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Create vector creating the blobs found by the detector
    vector<KeyPoint> blobs;

    while (true)
    {
        // Proces next frame
        video >> frame;

        // If there is no next frame, exit
        if (frame.empty())
        {
            break;
        }

        // Copy frame to src
        src = frame.clone();

        // Convert frame to grayscale
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        // Detect blobs
        detector->detect(frame, blobs);

        // Draw blobs
        drawKeypoints(src, blobs, src, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Display the number of dices
        String SumOfDices = format("Total number: %i", static_cast<int>(blobs.size()));
        putText(src, SumOfDices, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(83, 84, 198), 2, LINE_AA);

        // Display the frame
        imshow("DiceRecognition", src);

        // Close window with ESC key
        if (waitKey(30) == 27)
            break;
    }

    waitKey(1);
    video.release();
    destroyAllWindows();

    return 0;
}