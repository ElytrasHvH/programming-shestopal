CC = clang
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla
LIBRARY_NAME = libmodule-library.a

.PHONY: clean prep compile check

clean:
	rm -rf dist
	rm -rf ../lib
prep:
	mkdir -p dist
	mkdir -p ../lib

compile: $(LIBRARY_NAME)

$(LIBRARY_NAME): dist/lib.o
	ar rcs ./dist/$(LIBRARY_NAME) $<
	cp ./dist/$(LIBRARY_NAME) ../lib/$(LIBRARY_NAME)
	cp ./src/lib.h ../lib/lib.h

dist/lib.o: src/lib.c
	$(CC) $(C_OPTS) -c $^ -o $@

test: libmodule-library.a
	$(CC) $(C_OPTS) -o dist/test.bin test/test.c -Ldist -lmodule-library -lcheck -lm -lsubunit

check:
	clang-format -i src/*.[ch]
	clang-format --verbose --Werror src/*
	clang-tidy src/*.c --checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump

all: clean prep check compile test
