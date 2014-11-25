cmake_minimum_required(VERSION 2.8.9)
project(slg)
include_directories("${CMAKE_SOURCE_DIR}")
add_library(slg slgGraphics.cpp slgGraphics.h realFFTW.cpp realFFTW.h slgCircularBuffer.cpp slgCircularBuffer.h Thread.h Thread.cpp slgUtils.cpp slgUtils.h)