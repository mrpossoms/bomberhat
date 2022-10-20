cmake_minimum_required(VERSION 3.10)

project(gamma VERSION 0.0.0 LANGUAGES CXX)

set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set_property(TARGET sim PROPERTY CXX_STANDARD 11)

add_subdirectory(gitman_sources/ode)
add_subdirectory(sim)

include_directories(gitman_sources/xmath.h/inc)
