#include "preprocessor.hpp"

ResizePreprocessor::ResizePreprocessor(int width, int height){
    width_ = width;
    height_ = height;
}

cv::Mat ResizePreprocessor::process(const cv::Mat& input) {
    cv::Mat resized;
    cv::resize(input, resized, cv::Size(width_, height_));
    return resized;
}

cv::Mat GrayscalePreprocessor::process(const cv::Mat& input){
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat NormalizePreprocessor::process(const cv::Mat& input){
    //Apply Clahe
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0, cv::Size(8,8));
    cv::Mat enhanced;
    clahe->apply(input, enhanced);

    //Back to BGR
    cv::Mat result;
    cv::cvtColor(enhanced, result, cv::COLOR_GRAY2BGR);
    return result;
}

DenoisePreprocessor::DenoisePreprocessor(int kernelSize){
    kernelSize_ = kernelSize;
}
cv::Mat DenoisePreprocessor::process(const cv::Mat& input){
    cv::Mat blurred;
    cv::GaussianBlur(input, blurred, cv::Size(kernelSize_, kernelSize_), 0);
    return blurred;
}

EdgePreprocessor::EdgePreprocessor(int lowThresh, int highThresh){
    lowThresh_ = lowThresh;
    highThresh_ = highThresh;
}

cv::Mat EdgePreprocessor::process(const cv::Mat& input){
    cv::Mat gray;
    if(input.channels() == 3){
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    }
    else{
        gray = input; // already grayscale
    }

    cv::Mat edges;
    cv::Canny(gray, edges, lowThresh_, highThresh_);

    cv::Mat result;
    cv::cvtColor(edges, result, cv::COLOR_GRAY2BGR);

    return result;
}
