cmake_minimum_required(VERSION 3.10)

project(sindrom)
set(CMAKE_CXX_STANDARD 17)
add_library(Executer Executer.cpp)
target_link_libraries(Executer SindromPicture)
target_link_libraries(Executer Picture)