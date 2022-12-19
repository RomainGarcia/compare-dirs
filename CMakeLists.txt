cmake_minimum_required(VERSION 3.23)
project(compare-dirs)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/lib/)

add_executable(${PROJECT_NAME} src/main.cpp src/lib/md5/md5.cpp)
