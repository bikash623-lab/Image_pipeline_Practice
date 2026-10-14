#include "visualizer.hpp"

void Visualizer::drawDetections(cv::Mat& image, const std::vector<DetectionResult>& detections){
    for(int i = 0; i < detections.size(); i++){
    // draw bounding box
    cv::rectangle(image, detections[i].boundingBox, cv::Scalar(0,255,0), 2);

    // draw label
    cv::putText(image, "Object" + std::to_string(detections[i].id), cv::Point(detections[i].boundingBox.x, detections[i].boundingBox.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0), 1);

    }
}

void Visualizer::drawFPS(cv::Mat& image, double fps){
    cv::putText(image, "FPS:" + std::to_string((int)fps), cv::Point(20,40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255,0), 2);
}

void Visualizer::drawCount(cv::Mat& image, int count){
    cv::putText(image, "Object" + std::to_string(count), cv::Point(20,80), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,255,255), 2);
}

void drawInstruction(cv::Mat& image, const std::string& text){
    cv::putText(image, text, cv::Point(20, image.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255), 1);
}

bool Visualizer::saveImage(const cv::Mat& image, const std::string& filename){
    bool saved = cv::imwrite(filename, image);
    if(saved){
        std::cout << "Saved:" << filename << "\n";
    } else {
        std::cout << "Error: could not save" << filename << "\n";
    }

    return saved;
}