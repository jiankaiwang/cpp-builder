.PHONY: all
all: deploy

.PHONY: install
install: deploy

.PHONY: deploy
deploy: 
	@echo "Build the entry."
	g++ -std=c++11 -o main.o main.cc ../libs/libs.o

.PHONY: delete
delete:
	@echo "Delete the entry."
	rm -rf main.o

.PHONY: run
run:
	./main.o