CC=gcc
CFLAGS=-std=c99 -Wall

INCLUDES=-I include/

MAIN=src/main.c
SRC=$(filter-out $(MAIN), $(wildcard src/*.c))
TESTS=$(wildcard test/*.c)

all: $(SRC) $(MAIN)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(SRC) -o bin/matrix -lm

test: $(SRC) $(TESTS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS) $(SRC) -o bin/test -lm

clean:
	@rm bin/matrix

.PHONY: test
