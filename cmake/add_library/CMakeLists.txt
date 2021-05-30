cmake_minimum_required(VERSION 3.0)
project(addLibs VERSION 0.0.1)

# You can change the mode to STATIC (default), SHARED, MODULE (not working in this case)
# SHARED is the same to "cmake -D BUILD_SHARED_LIBS=TRUE"
add_library(
  libs
  libs.h
  libs.cc
)

add_executable(addLibs main.cc)

target_link_libraries(addLibs PRIVATE libs)