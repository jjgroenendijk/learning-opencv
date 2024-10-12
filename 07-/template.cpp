#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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
    
        CODE GOES HERE
    
    */

    return 0;
}