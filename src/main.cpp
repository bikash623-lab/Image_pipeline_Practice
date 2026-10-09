#include <opencv2/opencv.hpp>
#include <iostream>

int main(){
    cv:: Mat img = cv::imread("src/Tiger.jpg");

    if(img.empty()){
        std::cerr <<"Error: couldn't open the image." << std::endl;
        return -1;
    }

    std::cout <<"Width:"<<img.cols << std::endl;
    std::cout <<"Heigth:"<<img.rows << std::endl;
    std::cout <<"Channel:"<<img.channels() << std::endl;
    cv::Mat resized;
    cv::resize(img, resized, cv::Size(1080,1080));

    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    cv::rectangle(img, cv::Point(520, 165), cv::Point(990, 845), cv::Scalar(0,0,255), 2);
    cv::putText(img, "Tiger", cv::Point(500,150), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0,0,255), 2);

    cv:: Mat roi = img.clone();
    cv::Rect roitest(50,50, 500,500);
    roi(roitest) = cv::Scalar(0,0,0);

    // cv:: Mat cropped = img(cv::Rect(50,50,500,500)).clone();

    cv::Mat flipped;
    cv::flip(img, flipped, 1);
    
    cv::Vec3b pixel = img.at<cv::Vec3b>(300,300);
    std::cout << "Read_Pixel" << std::endl;
    std::cout << "Blue:" << (int)pixel[0] << std::endl;
    std::cout << "Green:" << (int)pixel[1] << std::endl;
    std::cout << "Red:" << (int)pixel[2] << std::endl;


    cv:: Mat pixelTest = img.clone();
    for(int row = 100; row < 300; row++){
        for(int col = 100; col < 300; col++){
            pixelTest.at<cv::Vec3b>(row, col) = cv::Vec3b(0,0,255);
        }

    }
    

    cv::Mat RedOnly = img.clone();
    for(int row = 0; row < RedOnly.rows; row++){
        for(int col = 0; col < RedOnly.cols; col++){
            cv::Vec3b& p = RedOnly.at<cv::Vec3b>(row, col);
            p[0] = 0;
            p[1] = 1;
        }
    }
    cv::imshow("Redonly", RedOnly);
    cv::imshow("pixeTest", pixelTest);
    cv::waitKey(0);

   // cv::imshow("cropped", cropped);
    cv::imshow("flip", flipped);
    cv::imshow("roi", roi);
    cv::imshow("Resize", resized);
    cv::imshow("original", img);
    cv::imshow("gray", gray);

    cv::waitKey(0);




    return 0;
}