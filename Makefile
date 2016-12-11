CC=gcc
CFLAGS=-Wall 

INCLUDES=-Iinclude/

MAIN=src/main.c
SRC=$(filter-out $(MAIN), $(wildcard src/*.c))
TESTS=test/tests.c

all: $(SRC) $(MAIN)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(SRC) -o bin/matrix

test: $(SRC) $(TESTS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS) $(SRC) -o bin/test

clean:
	@rm bin/matrix
	
.PHONY: test
