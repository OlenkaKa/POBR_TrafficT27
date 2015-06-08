cmake_minimum_required(VERSION 2.8)

project( POBR )

find_package( OpenCV REQUIRED )

add_executable( POBR main.cpp )

target_link_libraries( POBR ${OpenCV_LIBS} )
