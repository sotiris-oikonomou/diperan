########################################################################################################################################################
###
### This file is part of the Diperan project.
###
########################################################################################################################################################

### @file                       Diperan/CppUtility/CMakeLists.txt
### @author                     Sotiris Oikonomou <sotoik@gmail.com>
### @date                       15 May 2019

########################################################################################################################################################

## Project Properties

SET (PROJECT_NAME "Diperan")
SET (PROJECT_DESCRIPTION "A distributed system information and benchmarking statistics daemon.")
SET (PROJECT_PATH "Diperan")
SET (PROJECT_PACKAGE_NAME "diperan")
SET (PROJECT_LICENSE "LGPL")
SET (PROJECT_VENDOR_CONTACT "sotoik@gmail.com")

########################################################################################################################################################

## Setup

### Compatibility Check

CMAKE_MINIMUM_REQUIRED (VERSION "2.8.12" FATAL_ERROR)

### Paths

SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

### Policies

CMAKE_POLICY (SET "CMP0048" NEW)

########################################################################################################################################################

## Project Configuration

PROJECT (${PROJECT_NAME} VERSION ${PROJECT_VERSION_STRING} LANGUAGES "C" "CXX")

########################################################################################################################################################

## Targets
if (WIN32)
    SET (EXECUTABLE_NAME "${PROJECT_PACKAGE_NAME}.exe")
else ()
    SET (EXECUTABLE_NAME "${PROJECT_PACKAGE_NAME}")
endif ()

SET (EXECUTABLE_TARGET ${EXECUTABLE_NAME})

FILE (GLOB_RECURSE EXE_HEADERS "${PROJECT_SOURCE_DIR}/include/*.hpp")
FILE (GLOB_RECURSE EXE_SRCS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.cxx")

ADD_EXECUTABLE (${EXECUTABLE_TARGET} ${EXE_SRCS})

ADD_DEPENDENCIES (${EXECUTABLE_TARGET} ${SHARED_LIBRARY_TARGET})

TARGET_INCLUDE_DIRECTORIES (${EXECUTABLE_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${EXECUTABLE_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/include")

TARGET_LINK_LIBRARIES (${EXECUTABLE_TARGET} "pthread")
TARGET_LINK_LIBRARIES (${EXECUTABLE_TARGET} ${SHARED_LIBRARY_TARGET})

SET_TARGET_PROPERTIES (${EXECUTABLE_TARGET} PROPERTIES VERSION ${PROJECT_VERSION_STRING} OUTPUT_NAME ${EXECUTABLE_NAME} CLEAN_DIRECT_OUTPUT 1)

INSTALL (TARGETS ${EXECUTABLE_TARGET} DESTINATION ${INSTALL_BIN} COMPONENT "applications")

########################################################################################################################################################
