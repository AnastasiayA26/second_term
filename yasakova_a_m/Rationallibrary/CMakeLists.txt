cmake_minimum_required(VERSION 3.23)
project(Rationallibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(rational rational.cpp rational.h)
