CC=gcc
CFLAGS=-Wall 

INCLUDES=-Iinclude/

MAIN=src/main.c
SRC=$(filter-out $(MAIN), $(wildcard src/*.c))

all: $(SRC) $(MAIN)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(SRC) -o bin/matrix

clean:
	@rm bin/matrix
