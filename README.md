# Huffman Compression and Decompression

This project implements Huffman compression and decompression algorithms in C. The code is split into several modules for better organization and maintainability.

## File Structure

- `huffman.h`: Header file containing struct definitions and function prototypes.
- `huffman.c`: Implementation of Huffman algorithm functions.
- `compress.c`: Implementation of compression-related functions.
- `decompress.c`: Implementation of decompression-related functions.
- `main.c`: Main function that orchestrates the overall process.
- `Makefile`: Makefile to compile the project.
- `README.md`: This documentation file.

## Compilation

To compile the project, run the following command in the terminal:

```sh
make
```

This will create an executable named huffman.
The program expects an input file named input.txt in the same directory. It will generate two output files: codes.dat and output.dat.
To run the program, execute:
./huffman
Follow the on-screen instructions to compress and decompress the input file.
"# Huffman" 
