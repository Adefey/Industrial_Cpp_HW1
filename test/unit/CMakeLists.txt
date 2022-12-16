cmake_minimum_required(VERSION 3.24)

project(calculator_unit_test)

find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC")

add_executable(UnitTest main.cpp ../../src_lib/calculator.cpp)

set_property(SOURCE ../../src_lib/calculator.cpp APPEND PROPERTY COMPILE_OPTIONS "-coverage")

target_include_directories(UnitTest PUBLIC ../../include ${GTEST_INCLUDE_DIRS})

target_link_directories(UnitTest PUBLIC .)

target_link_libraries(UnitTest PUBLIC ${GTEST_LIBRARIES} pthread gcov gtest)
