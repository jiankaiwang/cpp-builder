# cmake

The cmake is a famous making tool for C, C++, Java etc. The cmake uses `CMakeLists.txt` to generate the `makefile`. 

## how to install cmake

The cmake can be installed via the following command. The cmake uses gcc/g++ compilers as the tool.

```sh
# install the prebuilt cmake
sudo apt-get install -y cmake
```

If there is no suitable cmake for installation, you can build the cmake from scratch.

```sh
sudo apt-get update
sudo apt-get install -y build-essential git

cd /tmp/
git clone https://github.com/Kitware/CMake.git

cd ./CMake
./bootstrap && make && sudo make install
```

If you can't install cmake, you can build the docker image and run the docker container.

```sh
docker build -t cmake:latest -f ./cmake/cmake.dockerfile .
docker run -it --rm cmake:latest cmake --version
```

## how to make C++ source files

Before you start building source files, it is required to create a `CMakeLists.txt` as the building guideline. The `CMakeLists.txt` can be located at different scope for different purposes, for example, for the project scope or the lib/package scope.

### add_executable

The simple example of building the executable in the CMakeLists.txt are the following.

```conf
cmake_minimum_required(VERSION 3.0)

# here simple is the project name
project(simple VERSION 0.0.1)

# here simple is the name of executable binary
# it would generate the binary name simple
add_executable(simple main.cc)
```

You can build the simple project.

```sh
cd ./cmake/simple

mkdir ./build
cd ./build

# cmake the simple project
cmake ..

# make the simple project
cmake --build .

# run the executable binary
./simple
```

### add_library

The next step is to add library to the building. The library is built as the static (`STATIC`) library (.a) by default. The `target_link_libraries` links the library. The scope `PRIVATE` is the relative to the project.

```conf
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
```

However you can change the building mode of library to `SHARED` (.o) or even `MODULE`. The following is the simple example of SHARED library.

```conf
add_library(
  libs SHARED
  libs.h
  libs.cc
)
```

After creating the `CMakeLists.txt`, you now can build the project.

```sh
cd ./cmake/add_library

mkdir ./build
cd ./build

# cmake the project
cmake ..

# make the project
cmake --build .

# run the executable binary
./addLibs
```

### add_subdirectory

It is commonplace to include external libraries while creating a service or application. Compare to the `add_library`, `add_subdirectory` is used in including external resources which contains a structural directories. In practical, the subdirectory may contain its own `CMakeLists.txt`.

If including the subdirectory, the `add_subdirectory` section must be added into the project's `CMakeLists.txt`.

Before getting strarted, let's take a look at the structure of source code.

```text
+ add_subdirectory
  + libs
    + main
    + src               // the target included
    - CMakeLists.txt
  + main
    - main.cc           // the target built
    - CMakeLists.txt
  - CMakeLists.txt      
```

We are going to build a binary under `main/main.cc`, and this script includes the library under `libs/src`. Both of them are different subdirectories and modules. You can see there are three `CMakeLists.txt`. They are under the project level and the module level. For the module level, you have to define how to use the resources of the module for building the project.

First let's edit the `CMakeLists.txt` at the project level (the path to `add_subdirectory/CMakeLists.txt`).

```conf
cmake_minimum_required(VERSION 3.0)
project(addLibs VERSION 0.0.1)

// there are two different subdorectories for building
// notice the sequence is important
// building the libs first and then main
add_subdirectory(libs)
add_subdirectory(main)
```

Next, we are going to edit the `CMakeLists.txt` at the module level at `add_subdirectory/libs/CMakeLists.txt`. You have to define how the main script includes the resources.

```conf
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
```

* Define the library that is included in the main script by using `add_library`.
* Define the path for how to include in other scripts by using `target_include_directories`. In this case, other scripts can simply use `libs.h` instead if `src/libs.h` because of the definition of `target_include_directories` to the `src`.
* You can also define lots of environment variables for compiling by using `target_compile_definitions`. Here we define the `LIBS_VERSION` to `1.0.0`.

**Notice the second parameter used in the latest two definitions (`PUBLIC`).** There are three modes available in CMAKE, they are `PUBLIC`, `PRIVATE`, and `INTERFACE`.

* `PUBLIC`: available for all scopes of scripts in the project
* `PRIVATE`: available only for self scope of scripts in the module
* `INTERFACE`: available for those scripts allowed to access the module

In general, you don't need to modify the libraries that you want to include. However you have to define the scope of and how to use them in the `CMakeLists.txt`.

After understanding the `CMakeLists.txt` at the module level, you now can program the main script and its `CMakeLists.txt`.

```cpp
// filename: add_subdirectory/main/main.cc
#include <iostream>
#include <cstdlib>
#include <vector>

// to include libs.h, because the path defined in target_include_directories
// on the CMakeLists.txt under the libs
#include "libs.h"

void PrintLibsVer() {
  // LIBS_VERSION is defined in CMakeLists.txt under the directory libs.
  std::cout << "The Libs version: " << LIBS_VERSION << std::endl;
}

int main(int argv, char* args[]) {
  PrintLibsVer();

  std::vector<int> checkVect = {-1, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11};
  for(int i = 0 ; i < checkVect.size(); i++) {
    try {
        std::cout << "Number " << checkVect[i] << " is a prime number? " << std::IsPrimeNum(checkVect[i]) << std::endl;
    } catch (std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
    }
  }
}
```

The above is the example for using custom library (`libs.h`) and using the compiling environment variables (`LIBS_VERSION`). The following is the `CMakeLists.txt` at the main script level.

```conf
add_executable(entry main.cc)

target_link_libraries(entry PRIVATE libs)
```

* You want to build an executable binary by using `add_executable` named `entry` to script `main.cc`. 
* You have to link the library while compiling by using `target_link_libraries`. Link the library named `libs` with the executable binary named `entry`.

After the above scripting, you now can cmake the whole project like the previos operations.

```sh
cd add_subdirectory

mkdir ./build
cd ./build

cmake ..
cmake --build .

./main/entry
```