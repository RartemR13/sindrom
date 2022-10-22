cmake_minimum_required(VERSION 3.10)

project(sindrom)

add_library(Executer Executer.cpp)
target_link_libraries(Executer SindromPicture)
target_link_libraries(Executer Picture)