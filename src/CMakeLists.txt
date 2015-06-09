set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_definitions(-std=c++11)

file(GLOB files *.cpp)

find_package(OpenCV REQUIRED)

add_executable(POBR_TrafficT27 ${files})

target_link_libraries(POBR_TrafficT27 ${OpenCV_LIBS})
