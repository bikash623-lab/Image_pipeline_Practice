#include "detector.hpp"

ObjectDetector::ObjectDetector(int minArea) {
    minArea_ = minArea;
}

std::vector<DetectionResult> ObjectDetector::detect(const cv::Mat& input) {
    std::vector<DetectionResult> results;

    // separate contours variable — correct type
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(input, contours, hierarchy,
                     cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);

    int objCount = 0;
    for(int i = 0; i < contours.size(); i++) {
        if(cv::contourArea(contours[i]) < minArea_) continue;

        objCount++;

        // fill DetectionResult struct
        DetectionResult det;
        det.id          = objCount;
        det.boundingBox = cv::boundingRect(contours[i]);
        det.area        = cv::contourArea(contours[i]);
        results.push_back(det);  // add to results list
    }

    return results;  // outside loop ✅
}

void ObjectDetector::setMinArea(int minArea) {
    minArea_ = minArea;  // update minArea_
}

int ObjectDetector::getMinArea() const {
    return minArea_;
}