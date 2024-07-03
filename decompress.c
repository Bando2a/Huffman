#include "huffman.h"

void twosscomplement(char bin[8]) {
    int i;
    for (i = 0; i < 8; i++) {
        if (bin[i] == '1') {
            bin[i] = '0';
        } else {
            bin[i] = '1';
        }
    }
    i = 0;
    while (bin[i] == '1') {
        bin[i] = '0';
        i++;
    }
    bin[i] = '1';
}

void chartobin(char x, char bin[100]) {
    int y = x;
    int i = 0;
    if (y < 0) {
        y = -y;
        while (y > 0) {
            bin[i] = y % 2 + '0';
            y = y / 2;
            i++;
        }
        while (i < 8) {
            bin[i] = '0';
            i++;
        }
        bin[i] = '\0';
        twosscomplement(bin);
        _strrev(bin);
    } else {
        while (y > 0) {
            bin[i] = y % 2 + '0';
            y = y / 2;
            i++;
        }
        while (i < 8) {
            bin[i] = '0';
            i++;
        }
        bin[i] = '\0';
        _strrev(bin);
    }
}

void copy(char x[], char y[], int j) {
    int i;
    for (i = 0; i < strlen(y); i++) {
        x[j] = y[i];
        j++;
    }
    x[j] = '\0';
}

void decompress(codelist* h, int s, int arr[], int extrabits, bool flag) {
    char ch;
    int i = 0;
    int index = 0;
    char character[9];
    char* Binary = (char*)malloc(8 * (s + 2) * sizeof(char) + strlen(tmp));
    while (count != 0) {
        Binary[index] = tmp[index];
        count--;
        index++;
    }
    reset(tmp, i);
    for (i; i < s; i++) {
        chartobin(arr[i], character);
        copy(Binary, character, index);
        index += 8;
    }
    codelist* it = h;
    char test[100] = { '\0' };
    int x = 1;
    test[0] = Binary[0];
    for (i = 1; i < index - extrabits; i++) {
        for (it = h; it != NULL; it = it->next) {
            if (strcmp(it->code, test) == 0) {
                printf("%c", it->letter);
                reset(test, s);
                x = 0;
                break;
            }
        }
        test[x] = Binary[i];
        x++;
        test[x] = '\0';
    }
    if (flag == false) {
        while (x != 0) {
            tmp[count] = test[count];
            count++;
            x--;
        }
    }
    free(Binary);
}
