
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
    
    string image_path = "t1.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::vector<Cords> blackPixels = findBlackPixles(img);
    //std::vector<std::vector<Cords>> shapes = getShapes(blackPixels);
    //std::vector<Cords> edges = getShapeEdges(shapes, img.rows, img.cols);
    std::vector<Cords> edges = getAreas(blackPixels);
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
    img = drawRect(edges, img);
    imshow("f", img);

    waitKey(0);
}
