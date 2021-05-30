.PHONY: all
all: deploy

.PHONY: install
install: deploy

.PHONY: deploy
deploy: 
	@echo "Build a customized library."
	g++ -c libs.cc 
	g++ -std=c++11 -o main.o main.cc libs.o

.PHONY: delete
delete:
	@echo "Delete the built library."
	rm -rf main.o libs.o

.PHONY: run
run:
	./main.o