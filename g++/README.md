# makefile with g++

## make with makefile

The make tool uses the makefile as the building target. The makefile can be regarded as the sequential shell scripts or commands for the compiling progress. 

* Before you make the project, you need a `Makefile` located at the scope of the project. 
  * You can create a Makefile on the project level or the library level.

* The `PHONY` tag and section. The tag is specified to the actions you requested. You can pass the PHONY value via the make command.

```makefile
.PHONY: deploy
deploy: 
	@echo "Build the entry."
	g++ -std=c++11 -o main.o main.cc ../libs/libs.o
```

The above section shows the example of a PHONY tag. You can use `make deploy` to do the actions.

* The basic `make` commands. You can define the make command using the PHONY tag. However the following is the basic format of the make tool.

```sh
# -C: specifies the folder for what you request
make [-C <folder>] <PHONY-action>
```

In the project level, you can also make the makefile with another makefiles to build the whole project.

```makefile
.PHONY: run
run:
	make -C libs run
	make -C main run
```

## g++

The g++ is a compiler for compiling C++ files and is originated from GCC (GNU Compiler Collection). The relative tool to the c files is gcc. You can install the g++ and make via the following script.

```sh
sudo apt-get install -y build-essential
```

You can build a docker image and run the container for running the g++ compiler.

```sh
docker build -t gcc:latest -f ./g++/gcc.dockerfile .
docker run -it --rm gcc:latest g++ --version
```

The general process of generating the object files is composed of 3 steps, they are `compiling`, `assembling`, and `linking`. You can use the `g++` to process the source code into different steps.

```sh
# only compile the source
g++ -o ./libs/libs.o -c ./libs/libs.cc

# build the executable binaries 
g++ -std=c++11 -o ./main/main.o ./libs/libs.o ./main/main.cc
```

You can also only run preprocess and compilation steps and generate the assembly code.

```sh
g++ -o ./libs/libs.s -S ./libs/libs.cc
```

## g++ with makefile

Now let's put both together.

```sh
cd ./g++

# Usage: make [options]
#   building options: [all|libs|main]
#   deleting options: [delete-libs|delete-main|delete]
#   running  options: [run|run-all]
#   helping  options: [help]
make help

# make all resources
make all

# run the executable binaries
make run

# delete all compiled resources
make delete
```