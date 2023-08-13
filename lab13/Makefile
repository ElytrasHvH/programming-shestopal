CC = gcc
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla
V_FLAGS=--tool=memcheck --leak-check=full --show-reachable=yes --undef-value-errors=yes --track-origins=no --child-silent-after-fork=no --trace-children=no --error-exitcode=1
#-fsanitize=address -fsanitize=leak 
#can't use them with leack-check-test for some reason
.PHONY: clean prep compile check

clean:
	rm -rf dist

prep:
	mkdir dist

compile: main

main: dist/main.o dist/lib.o
	$(CC) $(C_OPTS) $^ -o ./dist/main.bin -lm

dist/main.o: src/main.c
	$(CC) $(C_OPTS) -c $^ -o $@

dist/lib.o: src/lib.c
	$(CC) $(C_OPTS) -c $^ -o $@

test: dist/test.o dist/lib.o
	$(CC) $(C_OPTS) $^ -o ./dist/test.bin -lcheck -lm -lsubunit

dist/test.o: test/test.c
	$(CC) $(C_OPTS) -c $^ -o $@

check:
	clang-format --verbose --Werror src/*
	clang-tidy src/*.c --checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump

doxy:
	doxygen Doxyfile  
leak-check: clean prep compile
	valgrind $(V_FLAGS) --log-file=dist/valgrind.log cat ./assets/input.txt | ./dist/main.bin 
leak-check-test: clean prep compile test
	valgrind $(V_FLAGS) --log-file=dist/valgrind.log ./dist/test.bin
#--xml=yes --xml-file=dist/valgrind.xml
all: clean prep check compile test doxy
