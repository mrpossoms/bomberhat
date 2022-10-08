cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project ("BH.CORE" LANGUAGES CXX)

# set(BH_CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(bh.core INTERFACE)

target_include_directories(bh.core INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

add_subdirectory(tests)