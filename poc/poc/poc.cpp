
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
    string image_path = "testF.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::vector<Cords> blackPixels = findBlackPixles(img);
    std::vector<std::vector<Cords>> shapes = getShapes(blackPixels);
    std::vector<Cords> edges = getShapeEdges(shapes, img.rows, img.cols);
    img = drawRect(edges, img);


    cout << shapes.size();
    imshow("f", img);
    //waitKey();


    waitKey(0);
}
