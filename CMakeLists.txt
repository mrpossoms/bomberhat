cmake_minimum_required(VERSION 3.10)

project(gamma VERSION 0.0.0 LANGUAGES CXX)

set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(gitman_sources/ode)
add_subdirectory(sim)

set_property(TARGET sim PROPERTY CXX_STANDARD 11)

# set(ODE_WITH_DEMOS OFF CACHE BOOL "" FORCE)
# set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)

include_directories(gitman_sources/xmath.h/inc)
