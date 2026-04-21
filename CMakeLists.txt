cmake_minimum_required(VERSION 4.2)
project(QuantCore)

set(CMAKE_CXX_STANDARD 17)

add_executable(QuantCore
        main.cpp
        TaskQueue.h
        ThreadPool.h)
