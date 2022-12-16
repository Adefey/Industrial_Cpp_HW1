cmake_minimum_required(VERSION 3.24)

project(calculator_library)

add_library(calculator STATIC calculator.cpp)

target_include_directories(calculator PUBLIC ../include)
