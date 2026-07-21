cmake_minimum_required(VERSION 3.16)

project(LinLinZongZong)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(

    linlinzongzong 

    src/main.cpp

    src/model/Transaction.cpp
)
