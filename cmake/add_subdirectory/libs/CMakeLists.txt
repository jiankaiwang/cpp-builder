add_library(
  libs
  src/libs.h
  src/libs.cc
)

# expose the path "${CMAKE_CURRENT_SOURCE_DIR}/src" to the public entry point
target_include_directories(libs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# you can also define lots of environment variables for compiling
# notice the PUBLIC, PRIVATE, and INTERFACE modes
target_compile_definitions(libs PUBLIC LIBS_VERSION="1.0.0")