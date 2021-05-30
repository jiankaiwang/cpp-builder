# Clang++ and LLVM

The clang++ is another C++ compiler. It is supported by Apple Inc. and is also available for Objective-C. The clang++ is the frontend of LLVM. LLVM is designed for specifying hardwares.

You can build a docker image for both clang++ and LLVM.

```sh
# build the docker image
docker build -t clang-llvm:latest -f ./clang++-llvm/clang-llvm.dockerfile .

# run the container
docker run -it --rm -v $PWD/code:/tmp/code clang-llvm:latest bash

# clang++
docker run -it --rm clang-llvm:latest clang++ --version

# llc
docker run -it --rm clang-llvm:latest llc --version 
```

* The clang++ converts the source code into intermediate representations (IR) in the format of AST (Abstract Syntax Tree). The example of such IR is LLVM Bitcode.
* The LLVM compiles the IR into the machine code based on hardware platforms.

```sh
# make sure that clang++ exists
clang++ --version

# or you can docker run the container for clang++ and llvm
docker run -it --rm -v $PWD/clang++-llvm:/tmp/clang++-llvm clang-llvm:latest bash

# generate the intermediate representations (IR)
# -O2: optimization level 2
# -S:  Only run preprocess and compilation steps
# -emit-llvm: use the llvm representation for assembler and object files
# compile the libraries
clang++ -O2 -S -fno-use-cxa-atexit -emit-llvm -o ./libs/libs.ll ./libs/libs.cc
clang++ -O2 -S -fno-use-cxa-atexit -emit-llvm -o ./main/main.ll ./main/main.cc

# if the source code contains no customized library
# you can run the IR using lli command
lli ./main/main.ll

# opt is a tool to optimize the IR
opt -S -globalopt -loop-simplify -O2 -mem2reg ./libs/libs.ll -o ./libs/libs.opt
opt -S -globalopt -loop-simplify -O2 -mem2reg ./main/main.ll -o ./main/main.opt

# LLVM static compiler to generate assembly code
llc -O2 -mcpu=x86-64 -o ./libs/libs.s ./libs/libs.opt
llc -O2 -mcpu=x86-64 -o ./main/main.s ./main/main.opt

# on the target machine
clang++ -o ./main/main.o ./main/main.s ./libs/libs.s

# clean the generated resources
rm -rf ./libs/libs.ll ./libs/libs.o ./libs/libs.opt ./libs/libs.s
rm -rf ./main/main.ll ./main/main.o ./main/main.opt ./main/main.s
```

The above is the full process using both clang++ and LLVM. However, clang++ now implements the whole process from compiling to executable binaries.

```sh
# the compiling process from compiling source codes to executable binaries
clang++ -o ./main/main.o ./main/main.cc ./libs/libs.cc
```

