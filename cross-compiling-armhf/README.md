# Cross Compiling for armhf

In the following example, you will learn how to cross compile C++ source code for armhf, but in x86_64 platform. In the example, you are going to build a binary for Raspberry 3B/4, but all of the procedures were finished in x86_64. After you build the binary, you can copy the binary to the armhf platform for execution. 

In details, you need two necessary types of tools.
* `toolchain`: The toolchain is a series of compiling, assembling, and linking tools for the specific platform, and is released accompanying by the platform usually.
* `dependency tools or libraries`: It depends on the target platform. For the following example, you will need a `crossbuild-essential-armhf` tool set. If diving into the set, for example, you will find out the `lib32z1` is necessary for 64 bit platform to recognize the 32 bit executor.

You can simply build the docker image and run the container for the environment of building armhf apps.

```sh
cd ./cross-compiling-armhf

# build the docker image
docker build -t armhf_cross_compile -f ./build.dockerfile .

# run the container and compile the binary
cd ..
docker run -it --rm -v ${PWD}/cross-compiling-armhf:/tmp/cc armhf_cross_compile bash 
```

The environment inside the container is prepared for building armhf apps.

```sh
# check the g++ version
arm-linux-gnueabihf-g++ --version

# cross compiling
cd /tmp/cc/srcs
arm-linux-gnueabihf-g++ -o mmth.o -c mmth.cpp
arm-linux-gnueabihf-g++ -o ./main.o ./main.cpp ./mmth.o

# using file to look up the information of the binary
#
# ./main.o: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, for GNU/Linux 2.6.32, not stripped
#
file ./main.o
```

Then you can copy the binary to the armhf platform and then executing it. 

```sh
# in the armhf platform
# Tanh(3):0.995055
./main.o
```

Most of processes of cross compiling are similar.
