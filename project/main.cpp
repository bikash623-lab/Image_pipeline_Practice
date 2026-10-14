#include <iostream>
#include <chrono>
#include "acquisition/acquisition.hpp"
#include "preprocessing/preprocessor.hpp"
#include "detection/detector.hpp"
#include "output/visualizer.hpp"

int main(){
    // Steup Acquisition
    Acquisition sim("C:\Bikash_work_folder\OpenCv\project\images");
    if(!sim.hasFrames()){
        std::cout <<"No images found!\n";
        return -1;
    }
    std::cout << "Found" << sim.totalFrames() << "images\n";


    // Setup Pipeline
    std::vector< std::unique_ptr <Preprocessor>> pipeline;
    pipeline.push_back(std::make_unique<ResizePreprocessor> (640,480));
    pipeline.push_back(std::make_unique<DenoisePreprocessor>(5));
    pipeline.push_back(std::make_unique<EdgePreprocessor> (50, 150));

    // Setup Detector
    ObjectDetector detector(500); //minArea = 500

    // Steup Visualizer
    Visualizer visualizer;

    // FPS counter
    auto prevTime = std::chrono::steady_clock::now();
    int screenshotNum = 0;


    // Main Loop

    while (true){
        //get nextFrame
        cv::Mat frame = sim.nextFrame();
        cv::Mat processed = frame.clone();
        // run each preprocessor step on processed frame
        for (auto& step : pipeline){
            processed =  step->process(processed);
        }
        
        // Detect objects
        auto detections = detector.detect(processed);

        //calculate FPS
        auto currTime = std::chrono::steady_clock::now();
        double fps = 1.0/std::chrono::duration<double>(currTime - prevTime).count();
        prevTime = currTime;
        
        // Draw results on original frame
        cv::Mat result = frame.clone();
        visualizer.drawDetections(result, detections);
        visualizer.drawFPS(result, fps);
        visualizer.drawCount(result, detections.size());
        visualizer.drawInstruction(result, "ESC= quit S = save R = reset");

        // Display
        cv::imshow("Pipeline", result);
        cv::imshow("Processed", processed);

        // Key controls
        int key = cv::waitKey(3000); //300 between images
        if(key == 27) break;
        
        if(key == 's' || key =='S'){
            screenshotNum++;
            visualizer.saveImage(result, "screenshot_" + std::to_string(screenshotNum) + ".jpg");
            std::cout << "Saved screenshot " << screenshotNum << "\n";
        }

        if(key == 'r' || key =='R'){
            sim.reset();
            std::cout <<"Reset to first image\n";
        }

        if(key == '-'){
            detector.setMinArea(detector.getMinArea() - 100);
            std::cout <<"MinArea:" << detector.getMinArea() << "\n";
        }
    }
    cv::destroyAllWindows();
    return 0;
}