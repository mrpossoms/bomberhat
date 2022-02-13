# Install script for directory: /home/chris/Workspace/gamma/gitman_sources/ode

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xruntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so.8.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so.8"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/chris/Workspace/gamma/build/gitman_sources/ode/libode.so.8.0.0"
    "/home/chris/Workspace/gamma/build/gitman_sources/ode/libode.so.8"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so.8.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so.8"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/libode.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libode.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ode" TYPE FILE FILES
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/collision.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/collision_space.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/collision_trimesh.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/common.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/compatibility.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/contact.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/cooperative.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/error.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/export-dif.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/mass.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/matrix.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/matrix_coop.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/memory.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/misc.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/objects.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/ode.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odeconfig.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odecpp.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odecpp_collision.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odeinit.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odemath.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/odemath_legacy.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/rotation.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/threading.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/threading_impl.h"
    "/home/chris/Workspace/gamma/gitman_sources/ode/include/ode/timer.h"
    "/home/chris/Workspace/gamma/build/gitman_sources/ode/include/ode/precision.h"
    "/home/chris/Workspace/gamma/build/gitman_sources/ode/include/ode/version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/ode.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/ode-config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0" TYPE FILE FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/ode-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0" TYPE FILE FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/ode-config-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0/ode-export.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0/ode-export.cmake"
         "/home/chris/Workspace/gamma/build/gitman_sources/ode/CMakeFiles/Export/lib64/cmake/ode-0.16.0/ode-export.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0/ode-export-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0/ode-export.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0" TYPE FILE FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/CMakeFiles/Export/lib64/cmake/ode-0.16.0/ode-export.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/ode-0.16.0" TYPE FILE FILES "/home/chris/Workspace/gamma/build/gitman_sources/ode/CMakeFiles/Export/lib64/cmake/ode-0.16.0/ode-export-noconfig.cmake")
  endif()
endif()

