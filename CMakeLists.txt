cmake_minimum_required(VERSION 3.10)

project(sindrom)

add_executable(sindrom src/sindrom.cpp)

add_subdirectory(src/Picture)
target_link_libraries(sindrom Picture)
target_include_directories(sindrom PUBLIC src/Picture)

add_subdirectory(src/SindromPicture)
target_link_libraries(sindrom SindromPicture)
target_include_directories(sindrom PUBLIC src/SindromPicture)

add_subdirectory(src/CmdArgsParser)
target_link_libraries(sindrom CmdArgsParser)
target_include_directories(sindrom PUBLIC src/CmdArgsParser)

add_custom_command(
    TARGET sindrom
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/test/kaneki.bmp
            ${CMAKE_CURRENT_BINARY_DIR}/kaneki.bmp   
)
