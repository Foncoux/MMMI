# Install script for directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj

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
  if(EXISTS "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj" TYPE EXECUTABLE FILES "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj/bb.exe")
  if(EXISTS "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/bb.exe")
    endif()
  endif()
endif()

