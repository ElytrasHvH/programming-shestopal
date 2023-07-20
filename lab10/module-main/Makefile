CC = clang
LAB_OPTS = -I../module-library/src
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS)

.PHONY: clean prep compile check

clean:
	rm -rf dist

prep:
	mkdir dist

compile: main

main: dist/main.o
	$(CC) $(C_OPTS) $^ -o ./dist/main.bin -L../lib -lmodule-library

dist/main.o: src/main.c
	$(CC) $(C_OPTS) -I../lib -c $^ -o $@

check:
	clang-format --verbose --Werror src/*
	clang-tidy src/*.c --extra-arg=-I../module-library/src --checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump

all: clean prep check compile
