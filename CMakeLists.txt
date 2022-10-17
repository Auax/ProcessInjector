cmake_minimum_required(VERSION 3.22)
project("ProcessInjector")

set(CMAKE_CXX_STANDARD 20)

add_executable(ProcessInjector main.cpp dll/dll_inject.cpp Process/Process.cpp Process/Process.h)
