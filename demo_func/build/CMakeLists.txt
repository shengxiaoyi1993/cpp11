# cmake_minimum_required(VERSION 2.8)
# project(example)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 3.0.2)
project (demo_function VERSION 1.0)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME}
  "../src/main.cpp"
  "../src/export.cpp")

