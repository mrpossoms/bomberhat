cmake_minimum_required(VERSION 3.10)

project(gamma VERSION 0.0.0 LANGUAGES CXX)

set(ODE_WITH_DEMOS OFF CACHE BOOL "" FORCE)
set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(gitman_sources/ode)
add_subdirectory(sim)

set(ODE_WITH_DEMOS OFF CACHE BOOL "" FORCE)
set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)

include_directories(gitman_sources/xmath.h/inc)
