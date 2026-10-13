#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

//base class - all preprocessors inherit from this
class Preprocessor{
public:
    virtual ~Preprocessor() = default;
    virtual cv::Mat process(const cv::Mat& input) = 0;
};

// Step 1
class ResizePreprocessor : public Preprocessor{
public:
    ResizePreprocessor(int width, int height);
    cv::Mat process(const cv::Mat& input) override;
private:
     int width_, height_;
};


class GrayscalePreprocessor : public Preprocessor{
public:
    cv::Mat process(const cv::Mat& input) override;
};

class DenoisePreprocessor : public Preprocessor{
public:
    DenoisePreprocessor(int kernelSize=5);
    cv::Mat process(const cv::Mat& input) override;
private:
    int kernelSize_;
};

class NormalizePreprocessor : public Preprocessor{
public:
    cv::Mat process(const cv::Mat& input) override;
};

class EdgePreprocessor : public Preprocessor{
public:
    EdgePreprocessor(int lowThresh = 50, int highThresh = 150);
    cv::Mat process(const cv::Mat& input) override;
private:
    int lowThresh_, highThresh_;
};
