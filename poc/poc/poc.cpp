
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/videoio.hpp>
#include "Utils.h"


using namespace cv;
using namespace std;


int main()
{
    const clock_t begin_time = clock();
    // do something
    
    string image_path = "FT.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    cvtColor(img, img, COLOR_BGR2GRAY);
    threshold(img, img, 120, 255, THRESH_BINARY);
    cvtColor(img, img, COLOR_GRAY2BGR);
    std::vector<Cords> blackPixels = findBlackPixles(img);
    //std::vector<std::vector<Cords>> shapes = getShapes(blackPixels);
    //std::vector<Cords> edges = getShapeEdges(shapes, img.rows, img.cols);
    std::vector<Cords> edges = getAreasBin(blackPixels);
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
    imshow("f", img);
    waitKey(0);
    img = drawRect(edges, img);
    imshow("f", img);

    waitKey(0);
}
