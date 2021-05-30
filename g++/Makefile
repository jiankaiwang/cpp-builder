.PHONY: all
all: libs main

.PHONY: libs
libs:
	make -C libs all

.PHONY: main
main:
	make -C main all

.PHONY: delete-libs
delete-libs:
	make -C libs delete

.PHONY: delete-main
delete-main: 
	make -C main delete

.PHONY: delete
delete: delete-libs delete-main

.PHONY: run
run:
	make -C main run

.PHONY: run-all
run-all:
	make -C libs run
	make -C main run

.PHONY: help
help:
	@echo "Usage: make [options]"
	@echo "  building options: [all|libs|main]"
	@echo "  deleting options: [delete-libs|delete-main|delete]"
	@echo "  running  options: [run|run-all]"
	@echo "  helping  options: [help]"