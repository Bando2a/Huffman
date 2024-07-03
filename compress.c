#include "huffman.h"

void Compress(FILE* output, int sentence[], int n, bool flag) {
    int j = 0;
    int index = 0;
    int i = 0;
    codelist* it = head;
    char* bin = (char*)malloc(8 * (n + 10) * sizeof(char) + strlen(tmp));
    char x[8];
    while (count != 0) {
        bin[index] = tmp[index];
        count--;
        index++;
    }
    reset(tmp, index);
    for (i = 0; i < n; i++) {
        while (it->letter != sentence[i]) {
            it = it->next;
        }
        for (j = 0; j < it->codelength; j++) {
            bin[index] = it->code[j];
            index++;
            bin[index] = '\0';
        }
        it = head;
    }
    int NoOfBitsAdded = 0;
    if (flag == true) {
        while (index % 8 != 0) {
            bin[index++] = '0';
            bin[index] = '\0';
            NoOfBitsAdded++;
        }
    } else {
        while (index % 8 != 0) {
            tmp[count] = bin[index - 1];
            index--;
            bin[index] = '\0';
            count++;
        }
        _strrev(tmp);
    }
    int NoofBytes = strlen(bin) / 8;
    j = 0;
    while (NoofBytes != 0) {
        for (i = 0; i < 8; i++) {
            x[i] = bin[j];
            j++;
        }
        fprintf(output, "%c", getnumberfrombin(x));
        compressed++;
        NoofBytes--;
    }
    if (flag == true) {
        fprintf(output, "\n%d", NoOfBitsAdded);
    }
    free(bin);
}

void calcRatio(int original) {
    float percentage = (((float)original - compressed) / original) * 100;
    printf("The Compression Ratio Is %d : %f Compressed to Original = %%%f\n", compressed / compressed, (float)original / compressed, percentage);
}
