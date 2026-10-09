cmake_minimum_required(VERSION 3.20)
project(opencv_practice LANGUAGES CXX)

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

# Every src/*.cpp becomes its own executable named after the file,
# so each exercise is a new file and CMake needs no edits.
file(GLOB EXERCISES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
foreach(source ${EXERCISES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE ${OpenCV_LIBS})
endforeach()
