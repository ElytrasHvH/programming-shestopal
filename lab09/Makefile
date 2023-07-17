CC = clang
LAB_OPTS = -I./src
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS) $(MAC_OPTS)

.PHONY: clean prep compile run check doxygen test all

clean:
	rm -rf dist

prep:
	mkdir dist

compile: main.bin test.bin

test.bin: test/test.c src/lib.c
	$(CC) $(C_OPTS) $^ -fprofile-instr-generate -fcoverage-mapping -o ./dist/$@ -lcheck -lsubunit -lm

main.bin: src/main.c src/lib.c
	$(CC) $(C_OPTS) $^ -o ./dist/$@

run: clean prep compile
	./dist/main.bin

check:
	clang-format -i src/*.[ch]
	clang-format --verbose --Werror src/*
	clang-tidy src/*.c -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump

doxygen:
	doxygen Doxyfile

test: clean prep compile
	LLVM_PROFILE_FILE="dist/test.profraw" ./dist/test.bin
	llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
	llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.c
	llvm-cov show dist/test.bin -instr-profile=dist/test.profdata src/*.c --format html > dist/coverage.html

all: clean prep compile check doxygen
