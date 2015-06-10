cmake_minimum_required(VERSION 2.8)
project(POBR_TrafficT27)

find_package(OpenCV REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_definitions(-std=c++11)

file(GLOB files *.cpp)

add_executable(POBR_TrafficT27 ${files})
target_link_libraries(POBR_TrafficT27 ${OpenCV_LIBS})
