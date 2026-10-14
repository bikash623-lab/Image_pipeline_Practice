#pragma once
#include <opencv2/opencv.hpp>
#include "../detection/detector.hpp"
#include <vector>
#include <string>

class Visualizer{
public:
    // draw bounding boxes and labels on image
    void drawDetections(cv::Mat& image, const std::vector<DetectionResult>& detection);

    //draw FPS on image
    void drawFPS(cv::Mat& image, double fps);

    //draw object count on image
    void drawCount(cv::Mat& image, int count);

    //draw instruction text on image
    void drawInstruction(cv::Mat& image, const std::string& text);


    //save image to file
    bool saveImage(const cv::Mat& image, const std::string& filename);
    

};