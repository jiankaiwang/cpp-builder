# Bazel

The `bazel` is designed for building multiple programming languages and multiple platforms. It supports C, C++, Java, Go, etc. and can be applied on x86, arm, etc. It is hosted and developed by Google, and is also applied in lots of main frameworks, like Tensorflow, and angular.js, etc. It is designed to parallelly build the source code so that making the performance better than other tools.

## how to install bazel

Before you start using `bazel`, you should install it first. You can surf the link([Installing bazel](https://docs.bazel.build/versions/master/install.html)) to select the proper installation.

You can also build the `bazel` from scratch via docker container. However, bazel tools on most platforms can be downloaded directly from the official github respoitory. If requiring building bazel on specific platform, like arm 32-bit, you can build bazle via docker container by the following command.

```sh
cd ./bazel

# build the bazel making tool on ARM system
docker build --build-arg IMAGE=ubuntu:20.04 --build-arg BAZEL_VERSION=4.1.0 -t bazel:4.1.0 -f build.dockerfile .
```

You can also download the arm32-based bazel binary from the following links.
* [bazel-3.7.2-linux-arm32](https://storage.googleapis.com/jkw-gs/public/bazel-bin/bazel-3.7.2-linux-arm32)
* [bazel-4.1.0-linux-arm32](https://storage.googleapis.com/jkw-gs/public/bazel-bin/bazel-4.1.0-linux-arm32)

## how to make C++ source files

* There are two required files, one is `BUILD` file and the other is `WORKSPACE`.
  * The `BUILD` file is like the `CMakeLists.txt` in `cmake`. It provides with the building information under the scope, like the scope of library or the scope of project. **The subdirectory or folder with the `BUILD` file is called `lib`.**
  * The `WORKSPACE` file mostly located at the project level are used to pull the external dependencies, in other words, the source code is typically located outside the main repository.

* The following sections are defined in the `BUILD` file.
  * The `cc_library` section defines the resources considered as the libraries.
    * The `visibility` is defined for which scope is allowed to use this lib.
  * The `cc_binary` section defines the source code for generating the executable binaries.
  * The mark `//` is used to notify the subdirectory name. **Notice the relative path to the project and subdirectory.**
  * The mark `:` is used to notify the `library name` defined in BUILD.

```conf
cc_library(
  name = "libs",
  srcs = ["libs.cc"],
  hdrs = ["libs.h"],
  visibility = ["//main:__pkg__"]
)

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  deps = [":libs"]
)
```

The following is the example of builing the C++ source code by `bazel`.

```sh
cd ./bazel

# build the package
bazel build //libs:main
./bazel-bin/libs/main

# build the entry 
bazel build //main:entry
./bazel-bin/main/entry

# clean the compiled resources
bazel clean
```