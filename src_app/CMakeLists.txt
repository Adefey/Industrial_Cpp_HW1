cmake_minimum_required(VERSION 3.24)

project(calculator_application)

add_executable(Exe main.cpp)

target_include_directories(Exe PUBLIC ../include)

target_link_directories(Exe PUBLIC ../lib)

target_link_libraries(Exe PUBLIC calculator)

