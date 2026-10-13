#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/geometry.hpp>  // contourArea, boundingRect (OpenCV 5)
#include <vector>

// holds info about one detected object
struct DetectionResult {
    cv::Rect boundingBox;
    double   area;
    int      id;
};

class ObjectDetector {
public:
    ObjectDetector(int minArea = 500);

    // runs detection on input image
    // returns list of detected objects
    std::vector<DetectionResult> detect(const cv::Mat& input);

    // change minimum area threshold
    void setMinArea(int minArea);

    // get current minArea
    int getMinArea() const;

private:
    int minArea_;
};