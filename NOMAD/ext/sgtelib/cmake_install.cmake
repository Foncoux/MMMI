# Install script for directory: /home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/foncoux/Documents/nomad-v.4.3.1/build/release")
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
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so.2.0.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so.2.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/foncoux/Documents/nomad-v.4.3.1/build/release/ext/sgtelib/libsgtelib.so.2.0.3"
    "/home/foncoux/Documents/nomad-v.4.3.1/build/release/ext/sgtelib/libsgtelib.so.2.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so.2.0.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so.2.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/foncoux/Documents/nomad-v.4.3.1/build/release/ext/sgtelib/libsgtelib.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsgtelib.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/sgtelib" TYPE FILE FILES
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Defines.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Exception.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Kernel.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Matrix.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Metrics.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_CN.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Ensemble.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Ensemble_Stat.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Factory.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_KS.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Kriging.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_LOWESS.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_PRS.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_PRS_CAT.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_PRS_EDGE.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Parameters.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_RBF.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Surrogate_Utils.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/Tests.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/TrainingSet.hpp"
    "/home/foncoux/Documents/nomad-v.4.3.1/ext/sgtelib/src/sgtelib_help.hpp"
    )
endif()

