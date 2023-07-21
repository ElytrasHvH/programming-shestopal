CC = clang
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla
LIBRARY_NAME = libmodule-library.a

.PHONY: clean prep compile check

clean:
	rm -rf dist

prep:
	mkdir dist

compile: main

main: dist/main.o
	$(CC) $(C_OPTS) $^ -o ./dist/main.bin

dist/main.o: src/main.c
	$(CC) $(C_OPTS) -c $^ -o $@

test: dist/test.o
	$(CC) $(C_OPTS) $^ -o ./dist/test.bin -lcheck -lm -lsubunit

dist/test.o: test/test.c
	$(CC) $(C_OPTS) -c $^ -o $@

check:
	clang-format --verbose --Werror src/* test/*
	clang-tidy src/*.c test/*.c --checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump test/*.dump

all: clean prep check compile test
