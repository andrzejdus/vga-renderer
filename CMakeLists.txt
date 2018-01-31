cmake_minimum_required(VERSION 3.9.6)
project(mode13h)

set(CMAKE_CXX_STANDARD 98)

add_executable(mode13h
        src/main.cpp src/Mode13h.cpp src/Mode13h.h src/Bitmap.h src/Bitmap.cpp)
