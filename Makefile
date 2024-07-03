CC = gcc
CFLAGS = -Wall -Wextra -O2
DEPS = huffman.h
OBJ = main.o huffman.o compress.o decompress.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o huffman
