#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono> // for timing

int main(){
    //OPen video cap
    cv::VideoCapture cap(0);

    if(!cap.isOpened()){
        std::cerr <<"Error:couldn't open the camera.";
        return -1;
    }

    //Set resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    
    std::cout <<"WIdth:"<<cap.get(cv::CAP_PROP_FRAME_WIDTH) <<"\n";
    std::cout <<"Height:"<<cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";
    std::cout <<"FPS:"<<cap.get(cv::CAP_PROP_FPS) << "\n";

    auto prevTime = std::chrono::steady_clock::now();
    cv::Mat frame;

    while(true){
        cap >> frame; // grab frame
        if(frame.empty()) break;

        //calculate fps
        auto currTime = std::chrono::steady_clock::now();
        double fps = 1.0/std::chrono::duration<double>(currTime - prevTime).count();
        prevTime = currTime;
         cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    cv::Mat Blurred;
    cv::GaussianBlur(gray, Blurred, cv::Size(5,5), 0);
    
    cv::Mat Edges;
    cv::Canny(Blurred, Edges, 55, 90);

    cv::Mat Thresh;
    cv::threshold(frame, Thresh, 127, 255, cv::THRESH_BINARY);

    //Draw FPS on Frame

    cv::putText(frame, "FPS" + std::to_string((int)fps), cv::Point(20,40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255,0), 2);
    
    cv::imshow("Original", frame);
    cv::imshow("Edges", Edges);
    cv::imshow("Thresh",Thresh);
    cv::imshow("Blurred", Blurred);

    // waitKey pumps the GUI event loop; without it the windows never refresh
    if(cv::waitKey(1) == 'q') break;
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}