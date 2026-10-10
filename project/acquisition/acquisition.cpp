#include "acquisition.hpp"
#include <iostream>
#include <string>

Acquisition::Acquisition(const std::string& image_dir) //hamle .hpp constructor jasari create garako theim tei neh hunxa .cpp ma exact same
{
  // Load all the images jpg and png images from fodler
  cv::glob(image_dir + "/*.jpg", image_path_, false);
  
  std::vector<std::string> pngs;   
  cv::glob(image_dir + "/*.png", pngs, false);


  // combine jpg and png paths
  image_path_.insert(image_path_.end(), pngs.begin(), pngs.end());


  if(image_path_.empty()) /*yesle chai yo path or direction image xa ki nai check grxa*/{
    std::cerr <<"Acquisition no images found in: "
    << image_dir << std::endl;
  }
  else{
    std::cout <<"Acquisition loaded" << image_path_.size()
    <<"image from: " << image_dir << std::endl;
  }
  current_index_ = 0;
}

cv::Mat Acquisition::nextFrame(){
  if(image_path_.empty()){
    return cv::Mat();
  }

  //Read the image
  cv::Mat frame = cv::imread(image_path_[current_index_]);

  if(frame.empty()){
    std::cerr <<"Aquisition failed to load:" << image_path_[current_index_] << std::endl;
  }

  // Move to next, wrap around at end
  current_index_ = (current_index_ + 1) % image_path_.size();

  return frame;
}

bool Acquisition::hasFrames()const{
  return !image_path_.empty();
}

void Acquisition::reset(){
  current_index_ = 0;
}

int Acquisition::totalFrames() const{
  return (int)image_path_.size();
}