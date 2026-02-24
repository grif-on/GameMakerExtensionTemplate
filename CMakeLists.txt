cmake_minimum_required(VERSION 3.10.0)
project(GameMakerExtensionTemplate VERSION 0.0.1 LANGUAGES C CXX)

add_library(GameMakerExtensionTemplate SHARED dllmain.cpp exports.cpp)