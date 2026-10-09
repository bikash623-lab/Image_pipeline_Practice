#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

int main(){
    cv::Mat img = cv::imread("src/Tiger.jpg");
    if(img.empty()){
        std::cout << "Error: couldn't able to load the image." << std::endl;
        return -1;
    }

    cv:: Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat GausianBlur;
    cv::GaussianBlur(gray, GausianBlur, cv::Size(5,5), 0);

    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);

    cv::Mat edges;
    cv::Canny(GausianBlur, edges, 30, 90);


    //Morphologiacl operation
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));


    cv::Mat dilated, erode;
    cv::dilate(edges, dilated, kernel, cv::Point(-1,-1), 2);
    cv::erode(edges, erode, kernel, cv::Point(-1,-1), 1);

    //contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(dilated, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::cout << "Contours found: " << contours.size() << "\n";

    cv::Mat contourImg = cv::Mat::zeros(img.size(), img.type());
    cv::drawContours(contourImg, contours, -1, cv::Scalar(0,255,0), 2);

    cv::imshow("img", img);
    cv::imshow("gray", gray);
    cv::imshow("GausianBlur", GausianBlur);
    cv::imshow("Thresh", thresh);
    cv::imshow("Edges", edges);
    cv::imshow("dilate", dilated);
    cv::imshow("erode", erode);
    cv::imshow("ContourImg", contourImg);
     cv::waitKey(0);

    return 0;
}