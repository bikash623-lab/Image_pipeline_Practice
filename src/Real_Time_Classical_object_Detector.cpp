#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/geometry.hpp> // OpenCV 5: contourArea/boundingRect live here, not in opencv.hpp
#include <chrono>
#include <vector>

int main(){
    // 1. Open Camera
    cv::VideoCapture cap(0);

    if (!cap.isOpened()){
        std::cerr <<"Eror: couldn't open the camera.";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    
    // 2. Video Writer
    int fourcc = cv::VideoWriter::fourcc('m','p','4','v');
    cv::VideoWriter writer("recording.mp4", fourcc, 30.0, cv::Size(1280,720));

    std::cout <<"Width:"<< cap.get(cv::CAP_PROP_FRAME_WIDTH) <<"\n";
    std::cout <<"Height:"<< cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";
    std::cout <<"FPS:" << cap.get(cv::CAP_PROP_FPS) << "\n";

    // 3. Settings
    int MinArea = 600;
    bool showContours = true;
    int screenshotNum = 0;

    // 4. FPS contours
    auto prevTime = std::chrono::steady_clock::now();

    cv::Mat frame;

    while(true){
        cap >> frame;
        if(frame.empty()) break;

        // 5. Process Frame
        cv:: Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv:: Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5,5), 0);

        cv:: Mat edges;
        cv::Canny(blurred, edges, 30, 100);

        cv:: Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

        cv:: Mat closed;
        cv::dilate(edges, closed, kernel, cv::Point(-1,-1), 2);


        // 6. Find Contours
        std::vector <std::vector <cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(closed, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        // 7. Draw Detections
        cv:: Mat result = frame.clone();
        int objCount = 0;

        for(int i = 0; i < contours.size(); i++){
            if(cv::contourArea(contours[i]) < MinArea) continue;

            objCount++;
            cv::Rect box = cv::boundingRect(contours[i]);

            // Draw box
            cv::rectangle(result, box, cv::Scalar(0,255,0), 2);

            // Draw Label
            cv::putText(result, "Object" + std::to_string(objCount), cv::Point(box.x, box.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0), 1);
        }

        // 8. FPS Cpunter
        auto currTime = std::chrono::steady_clock::now();
        double fps = 1.0/std::chrono::duration<double>(currTime - prevTime).count();
        prevTime = currTime;

        
        cv::putText(result, "FPS: " + std::to_string((int)fps), cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        // 9. Object Count
        cv::putText(result, "Objects:" + std::to_string(objCount), cv::Point(20,80), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255,0), 2);


        // 10. Instruction on screen
        cv::putText(result, "ESC=quit S=screenshot C=toggle", cv::Point(20, frame.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

        // 11. Write to videp
        writer.write(result);

        // 12. Display
        cv::imshow("Classical Detector", result);

        if(showContours){
            cv::imshow("Edges", closed);
        }

        // 13. Key Controls

        int key = cv::waitKey(1);

        if(key == 27) break; //ESC - quit++-----++++++++

        if(key == 's' || key == 'S'){
            // save screenshot
            screenshotNum++;
            std::string filename = "screenshot_" + std::to_string(screenshotNum) + ".jpg";
            cv::imwrite(filename, result);

            std::cout <<"Saved:" << filename << "\n";
        }


        if(key=='c' || key =='C'){
            // toggle contour view
            showContours = !showContours;
            // destroyWindow throws if the window is already gone, so only call it once, here
            if(!showContours) cv::destroyWindow("Edges");
            std::cout << "Contours:" << (showContours ? "ON":"OFF") << "\n";
        }

        if(key == '+'){
            MinArea += 100;
            std::cout <<"Min area:"  << MinArea << "\n";
        }

        if(key == '-' && MinArea > 100){
            MinArea -= 100;
            std::cout <<"MinArea:" << MinArea << "\n";
        }
    }
    writer.release();
    cap.release();
    cv::destroyAllWindows();
    return 0;
}