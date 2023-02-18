
if(NOT UNIX)
    message(FATAL_ERROR "Not a unix system.")
endif()

cmake_minimum_required (VERSION 3.16)

project( DSPPG
         DESCRIPTION "Just playing around with Digital Signal Processing"
         VERSION 0.0.1            
)

# set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE Debug)

add_library(${CMAKE_PROJECT_NAME} "")

add_subdirectory(submodules)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC m)


#-------------------------------------------------
# GNUPLOT
#-------------------------------------------------
# Check if Gnuplot is installed
# execute_process(COMMAND "which gnuplot" RESULT_VARIABLE GNUPLOT_PATH)
set(PROGRAM_NOT_FOUND_POSTFIX "-NOTFOUND")
find_program(GNUPLOT_INSTALL_PATH gnuplot)
if(NOT "${GNUPLOT_INSTALL_PATH}" STREQUAL "GNUPLOT_INSTALL_PATH${PROGRAM_NOT_FOUND_POSTFIX}")
  add_compile_definitions(GNUPLOT_IS_INSTALLED)
else()
  message(STATUS "GNUplot not installed. Plotting is disabled.")
endif()


#-------------------------------------------------
# LOGGING
#-------------------------------------------------
#
# log.c
include_directories(submodules/log.c/src)
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE build/submodules)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE log_c)


#-------------------------------------------------
# OWN CODE
#-------------------------------------------------
#
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
add_subdirectory(src)


#-------------------------------------------------
# TESTING
#-------------------------------------------------
#
# Unity
# Cmake and Unity example: https://www.poisel.info/posts/2019-07-15-cmake-unity-integration/
include(CTest)
add_subdirectory(test/Signals)
add_subdirectory(test/Statistics)
#
# Setup Memory Checker
# --> Run MemCheck using: ctest -R <testname> -D ExperimentalMemCheck
find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --track-origins=yes " )
#set( MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/valgrind_suppress.txt" )