CC=gcc
CFLAGS=-Wall 

SRC = matrix.c determinant.c

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o matrix

clean:
	@rm matrix
