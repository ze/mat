CC=gcc
CFLAGS=-Wall 

SRC = main.c matrix.c

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o matrix

clean:
	@rm matrix
