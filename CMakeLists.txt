cmake_minimum_required(VERSION 3.10.0)
project(ExampleExtension VERSION 0.0.1 LANGUAGES C CXX)

add_library(ExampleExtension SHARED dllmain.cpp ExampleExtension.cpp)