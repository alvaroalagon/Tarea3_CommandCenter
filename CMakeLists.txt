cmake_minimum_required(VERSION 4.2)
project(CommandCenter__)

set(CMAKE_CXX_STANDARD 20)

add_executable(CommandCenter__
        main.cpp
        CommandCenter.h
        CommandTypes.h
        CommandTypes.cpp
        Entity.h
        Entity.cpp)
