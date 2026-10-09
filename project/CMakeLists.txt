cmake_minimum_required(VERSION 3.20)
project(pipeline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fallback for the official prebuilt package extracted to C:\opencv.
# Ignored if OpenCV_DIR is passed with -D or set as an environment variable.
if(NOT OpenCV_DIR AND NOT DEFINED ENV{OpenCV_DIR} AND EXISTS "C:/opencv/build")
    set(OpenCV_DIR "C:/opencv/build")
endif()

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV ${OpenCV_VERSION} found in ${OpenCV_DIR}")

add_executable(pipeline
    main.cpp
    acquisition/acquisition.cpp
    preprocessing/preprocessor.cpp
    detection/detector.cpp
    output/visualizer.cpp
)

target_include_directories(pipeline PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(pipeline PRIVATE ${OpenCV_LIBS})
