CC=gcc
CFLAGS=-Wall

MAIN=matrix_solve.c

all: $(SRC)
	$(CC) $(CFLAGS) $(MAIN) -o matrix

clean:
	@rm matrix
