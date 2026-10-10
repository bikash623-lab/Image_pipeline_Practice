#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class Acquisition{
public:
    // Constructor - pass folder path of images
    Acquisition(const std::string& image_dir);

    // return next frame
    cv::Mat nextFrame();


    // true if images available
    bool hasFrames() const;

    // reset back to the first image
    void reset();

    // get total image count
    int totalFrames() const;

private:
    std::vector<std::string> image_path_;
    size_t current_index_;
}; 