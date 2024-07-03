#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct huffnode {
    int frequency;
    char letter;
} huffnode;

typedef struct Treenode {
    huffnode node;
    struct Treenode* left, * right, * parent;
} Treenode;

typedef struct Linkednode {
    Treenode value;
    struct Linkednode* next;
} Linkednode;

typedef struct codelist {
    char code[100];
    char letter;
    int codelength;
    struct codelist* next;
} codelist;

extern codelist* head;
extern char tmp[100];
extern int count;
extern int compressed;

Linkednode* insert(Linkednode* head, Treenode value, int priority);
Linkednode* removeFirst(Linkednode* head, Treenode* item);
int getfile(FILE* file);
void getlettercount(FILE* input, int* x);
Linkednode* frequencytable(FILE* file, Linkednode* head, bool* stat);
Treenode* huffmantree(Treenode* tree, Linkednode* head);
codelist* insertFirst(codelist* head, char letter, int code[], int i);
void GenHuffCodes(Treenode* tree, int arr[], int i);
void CodesFile(FILE* output);
int pwr(int x, int y);
int getnumberfrombin(char str[]);
void reset(char x[], int size);
void resetint(int x[], int size);
void Compress(FILE* output, int sentence[], int n, bool flag);
void calcRatio(int original);
void twosscomplement(char bin[8]);
void chartobin(char x, char bin[100]);
void copy(char x[], char y[], int j);
void decompress(codelist* h, int s, int arr[], int extrabits, bool flag);

#endif // HUFFMAN_H
