cmake_minimum_required(VERSION 3.16)
project(GoogleCppStyleDemos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(01_header_files)

add_executable(02_scoping 02_scoping.cc)
add_executable(03_classes 03_classes.cc)
add_executable(04_functions 04_functions.cc)
add_executable(05_ownership 05_ownership.cc)
add_executable(06_modern_cpp 06_modern_cpp.cc)
add_executable(07_naming 07_naming.cc)
add_executable(08_comments_formatting 08_comments_formatting.cc)
