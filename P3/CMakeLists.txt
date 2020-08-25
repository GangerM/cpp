cmake_minimum_required(VERSION 3.13)
project(P3)

set(CMAKE_CXX_STANDARD 17)

add_executable(P3 priorityqueue.cpp buildheap.cxx createteams.cxx teamdata.h teamdata.cpp priorityqueue.h)