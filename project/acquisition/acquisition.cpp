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
    std::cerr <<"Aquisition no images found in: "
    << image_dir << std::endl;
  }
  else{
    std::cout <<"Aquisition loaded" << image_path_.size()
    <<"image from: " << image_dir << std::endl;
  }
  current_index_ = 0;
}

cv::Mat Acquisition::nextFrame(){
  if(image_path_.empty()){
    return cv::Mat();
  }
  
}