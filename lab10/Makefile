CC = clang
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla
LIBRARY_NAME = libmodule-library.a

.PHONY: clean prep compile check doc

clean:
	rm -rf lib
	rm -rf module-library/dist
	rm -rf module-main/dist
	rm -rf dist

prep:
	mkdir -p lib
	mkdir -p module-library/dist
	mkdir -p module-main/dist

compile: $(LIBRARY_NAME) main

$(LIBRARY_NAME):
	cd module-library && $(MAKE) compile

main:
	cd module-main && $(MAKE) compile

check:
	cd module-library && $(MAKE) check
	cd module-main && $(MAKE) check

doxygen:
	doxygen Doxyfile

all: clean prep check compile doxygen
