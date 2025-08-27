CC = gcc
FLAGS = -Wall

.PHONY: clean test run_test default

default:
	@echo "Please specify a target."

# Creates and runs the test of this utility.
run_test: test
	./executable/test

test: executable/test

TS =\
test/listtest.c\
source/list.c

executable/test: $(TS) | executable
	$(CC) $(FLAGS) $(TS) -o $@

executable:
	mkdir -p $@

clean:
	rm -rf executable