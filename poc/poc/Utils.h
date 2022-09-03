#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/videoio.hpp>
#include "Cords.h"
#include <vector>
using namespace cv;
//finds all black pixels
std::vector<Cords> findBlackPixles(cv::Mat img)
{
    std::vector<Cords> res;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            //is black
            if (img.at<cv::Vec3b>(i, j) == cv::Vec3b(0, 0, 0))
            {
                res.push_back(Cords(j, i));
            }

        }
    }
    return res;
}

std::vector<std::vector<Cords>> getShapes(std::vector<Cords> blackPixels)
{
    std::vector<std::vector<Cords>> res;
    int shapeCount = 0;
    for (int n = 0; n < blackPixels.size(); n++)
    {
        std::cout << n+1 << "\\" << blackPixels.size() << std::endl;
        bool isNeeded = true;
        for (int i = 0; i < res.size() && isNeeded; i++)
        {
            for (int j = 0; j < res[i].size()&& isNeeded; j++)
            {
                if (blackPixels[n] == res[i][j])
                {
                    isNeeded = false;
                }
            }
        }
        if (isNeeded)
        {
            std::vector<Cords> temp;
            temp.push_back(blackPixels[n]);
            res.push_back(temp);
            for (int i = 0; i < blackPixels.size(); i++)
            {
                bool flag = false;
                bool alreadyEx = false;
                for (int j = 0; j < res[shapeCount].size() && !alreadyEx; j++)
                {
                    if (blackPixels[i].isCloseTo(res[shapeCount][j]))
                    {
                        flag = true;
                    }
                    if (blackPixels[i] == res[shapeCount][j])
                    {
                        alreadyEx = true;
                    }

                }
                if (flag && !alreadyEx)
                {
                    res[shapeCount].push_back(blackPixels[i]);
                }


            }
            
            shapeCount++;
        }
       
    }
    std::cout << "shapes found: " << res.size()<<std::endl;
    std::vector<std::vector<Cords>> resMerged;
    int mergedShapeCount = 0;
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << "check shape: "<<i<<"\\" << res.size() << std::endl;
        bool isNeeded = true;
        for (int k = 0; k < resMerged.size() && isNeeded; k++)
        {
            for (int j = 0; j < resMerged[k].size() && isNeeded; j++)
            {
                for (int m = 0; m < res[i].size() && isNeeded; m++)
                {
                    if (res[i][m] == resMerged[k][j])
                    {
                        isNeeded = false;
                    }

                }

            } 
        }
        if (isNeeded)
        {
            std::cout << "shapes merged!" << std::endl;
            resMerged.push_back(res[i]);
            for (int j = 0; j < res.size(); j++)
            {
                bool flag = false;
                if (i != j)
                {
                    for (int k = 0; k < resMerged[mergedShapeCount].size() && !flag; k++)
                    {
                        for (int m = 0; m < res[j].size() && !flag; m++)
                        {
                            if (resMerged[mergedShapeCount][k].isCloseTo(res[j][m]))
                            {
                                flag = true;
                                for (int n = 0; n < res[j].size(); n++)
                                {
                                    resMerged[mergedShapeCount].push_back(res[j][n]);
                                }
                            }
                        }
                    }
                }

            }
            mergedShapeCount++;
        }
       
    }
    std::cout << "shapes merged: " << res.size() <<" --> "<<resMerged.size() << std::endl;
    return resMerged;
    
}
std::vector<Cords> getShapeEdges(std::vector<std::vector<Cords>> shapes,int maxX,int maxY)
{
    std::vector<Cords> res;
    for (int n = 0; n < shapes.size(); n++)
    {
        const int l = 5;
        int upCords = maxY;
        int rightCords = 0;
        int leftCords = maxX;
        int downCords = 0;
        for (int i = 0; i < shapes[n].size(); i++)
        {
            if (shapes[n][i].y < upCords)
            {
                upCords = shapes[n][i].y - l;
            }
            if (shapes[n][i].x < leftCords)
            {
                leftCords = shapes[n][i].x - l;
            }
            if (shapes[n][i].x > rightCords)
            {
                rightCords = shapes[n][i].x + l;
            }
            if (shapes[n][i].y > downCords)
            {
                downCords = shapes[n][i].y + l;
            }
        }
        res.push_back(Cords(leftCords, upCords, rightCords, downCords));
    }
    return res;
}

std::vector<Cords> getAreas(std::vector<Cords> blackPixels)
{
    std::vector<Cords> res;
    int shapeCount = 0;
    //for each pixel
    for (int n = 0; n < blackPixels.size(); n++)
    {
        std::cout << n + 1 << "\\" << blackPixels.size() << std::endl;
        bool isNeeded = true;
        for (int i = 0; i < res.size() && isNeeded; i++)
        {
            //if pixel is not part of an area
            if (blackPixels[n].isInArea(res[i]))
            {
                isNeeded = false;
            }
        }
        if (isNeeded)
        {
            //creates new area
            Cords temp= Cords(blackPixels[n].x, blackPixels[n].y);
            res.push_back(temp);
            //adds all close pixels to new area
            for (int i = 0; i < blackPixels.size(); i++)
            {

                if (i!=n && blackPixels[i].isCloseToArea(res[shapeCount]))
                {
                    res[shapeCount].addToArea(blackPixels[i]);
                }
            }
            shapeCount++;
        }
    }

    //after areas found, merge close areas
    std::cout << "shapes found: " << res.size() << std::endl;
    std::vector<Cords> resMerged;
    
    int delta = -1;
    while (delta != 0)
    {
        resMerged.clear();
        int mergedShapeCount = 0;
        for (int i = 0; i < res.size(); i++)
        {
            std::cout << "check shape: " << i << "\\" << res.size() << std::endl;
            bool isNeeded = true;
            //if area is already a part of other area
            for (int k = 0; k < resMerged.size() && isNeeded; k++)
            {
                if (resMerged[k].isAreaCloseToArea(res[i]))
                {
                    isNeeded = false;
                }
            }
            if (isNeeded)
            {
                //creates new 'merged area'
                std::cout << "shapes merged!" << std::endl;
                resMerged.push_back(res[i]);
                for (int j = res.size() - 1; j >= 0; j--)
                {
                    bool flag = false;
                    if (i != j)
                    {
                        //merge all close areas
                        if (resMerged[mergedShapeCount].isAreaCloseToArea(res[j]))
                        {
                            resMerged[mergedShapeCount].addAreaToArea(res[j]);
                        }
                    }

                }
                mergedShapeCount++;
            }

        }
        delta = res.size() - resMerged.size();
        res = resMerged;
    }
    
    std::cout << "shapes merged: " << res.size() << " --> " << resMerged.size() << std::endl;
    return resMerged;

}


//draw rectangle around the edge of the shape
cv::Mat drawRect(std::vector<Cords> shapes, cv::Mat img )
{
    for (int n = 0; n < shapes.size(); n++)
    {
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                if (i == shapes[n].y && j >= shapes[n].x && j <= shapes[n].xMax || i == shapes[n].yMax && j >= shapes[n].x && j <= shapes[n].xMax)
                {
                    img.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
                }
                if (j == shapes[n].x && i >= shapes[n].y && i <= shapes[n].yMax || j == shapes[n].xMax && i >= shapes[n].y && i <= shapes[n].yMax)
                {
                    img.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
                }
            }
        }
    }
    return img;
}