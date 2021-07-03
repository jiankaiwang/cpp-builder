# C++ Builder

![](https://img.shields.io/badge/Language-C++-blue) 
![](https://img.shields.io/badge/Interface-Python\/C-orange)
![](https://img.shields.io/badge/Version-C++11-green)
![](https://img.shields.io/badge/Version-Python_3-green)

The C++ builder is a tutorial for demonstrating how to build a C++-based project by different approaches. 

The general process of generating the object files or executable binaries is composed of 3 steps, they are `compiling`, `assembling`, and `linking`. Different compilers implement parts of the above processes. The followings are the main compilers for compiling the C++ files. 

* [`g++`](g++): The g++ compiler now implements the whole process from compiling to linking, and generates the object executable binaries.
* [`clang++ with LLVM`](clang++-llvm): The Clang++ is the frontend of the pipeline and LLVM is the backend of the pipeline. The clang++ compling the source code into the intermediate representation (IR) and LLVM compiles the IR into the executable binaries based on different hardware platforms. 

In addition, we also demo how to build the whole project by the following making tools.

* [`make`](g++): The `make` is the elementary tool and easier understanding than the others. Here we will demo the make tool by makefiles and use the g++ compiler as the example.
* [`cmake`](cmake): The `cmake` is the famous making tool supporting C, C++, Java, etc. You can regard cmake as the powerful extensions for make. The cmake uses `CMakeLists.txt` to generate the makefile and then making the project.
* [`bazel`](bazel): The `bazel` is designed for building multiple programming languages and multiple platforms. It is hosted and developed by Google, and is also applied in lots of main frameworks, like Tensorflow, and angular.js, etc. 

In the modern system, the C++ source code is frequently embedded or wrapped by the higher programming languages, like `Python`. The following we list several approaches of wrapping C++ by Python.

* [`cpython`](cpython): In the first approach, we introduce how to wrap the C++ source code by the official supporting.
* [`ctypes`](ctypes): The second approach is to wrap the C++ source code by compiling it into the shared library, and then load the library in the Python runtime. The `ctypes` defines lots of data types and accessing methods for interacting.