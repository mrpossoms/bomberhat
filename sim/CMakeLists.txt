cmake_minimum_required(VERSION 3.10)



if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation.cpp)

add_executable(sim ${SOURCES})

target_include_directories(sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# link to the appropriate packages and libraries
find_package(OpenGL REQUIRED)
list(APPEND CMAKE_REQUIRED_INCLUDES ${OPENGL_INCLUDE_DIR})
list(APPEND CMAKE_REQUIRED_LIBRARIES ${OPENGL_LIBRARIES})

if(APPLE)
    find_package(GLUT REQUIRED)
    target_include_directories(sim PRIVATE ${GLUT_INCLUDE_DIR})
    target_link_libraries(sim PRIVATE ${GLUT_LIBRARIES})
else()
    find_package(X11 REQUIRED)
    target_include_directories(sim PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(sim PRIVATE ${X11_LIBRARIES})
endif()

target_include_directories(
  sim PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(
  sim PRIVATE ODE drawstuff)

target_link_libraries(sim PRIVATE ${OPENGL_LIBRARY})
