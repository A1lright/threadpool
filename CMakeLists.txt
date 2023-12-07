cmake_minimum_required(VERSION 3.26)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadPool main.cpp
        threadpool1.h
        threadsafe_queue.h)

target_link_libraries(ThreadPool pthread)
