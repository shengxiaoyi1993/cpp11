# cmake_minimum_required(VERSION 2.8)
# project(example)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 3.0.2)
project (demo_function VERSION 1.0)
#set( CMAKE_CXX_FLAGS "-std=c++11" )
#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
# --no-as-needed is required with gcc according to the MKL link advisor
#if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
#endif()

# Enable multithreading to use std::thread: Operation not permitted
set(CMAKE_CXX_FLAGS "-Wl,--no-as-needed -std=c++11 -O3 -Wall -fopenmp")


add_executable(${PROJECT_NAME}
  "../src/main.cpp"
  "../src/export.cpp"

  )

