cmake_minimum_required(VERSION 3.23)
project(projectc)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Rationallibrary)

add_executable(testlib testlib.cpp)
target_link_libraries(testlib rational)
#add_executable(Rationallibrary Rationallibrary/rational.cpp)
add_executable(main main.cpp)