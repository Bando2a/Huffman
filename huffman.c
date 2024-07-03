#include "huffman.h"

codelist* head = NULL;
char tmp[100] = { '\0' };
int count = 0;
int compressed = 0;

Linkednode* insert(Linkednode* head, Treenode value, int priority) {
    Linkednode* tmp = (Linkednode*)malloc(sizeof(Linkednode));
    if (head == NULL) {
        head = (Linkednode*)malloc(sizeof(Linkednode));
        head->value = value;
        head->value.node.frequency = priority;
        head->next = NULL;
    } else if (priority < head->value.node.frequency) {
        tmp->value = value;
        tmp->value.node.frequency = priority;
        tmp->next = head;
        head = tmp;
    } else {
        Linkednode* it = head;
        tmp->value = value;
        tmp->value.node.frequency = priority;
        while (it->next != NULL && it->next->value.node.frequency < tmp->value.node.frequency)
            it = it->next;
        tmp->next = it->next;
        it->next = tmp;
    }
    return head;
}

Linkednode* removeFirst(Linkednode* head, Treenode* item) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        *item = head->value;
        free(head);
        head = NULL;
    } else {
        *item = head->value;
        Linkednode* tmp = head->next;
        free(head);
        head = tmp;
    }
    return head;
}

int getfile(FILE* file) {
    int x;
    fseek(file, 0L, SEEK_END);
    x = ftell(file);
    rewind(file);
    return x;
}

void getlettercount(FILE* input, int* x) {
    char c;
    while ((c = getc(input)) != EOF) {
        *x += 1;
    }
    *x += 1;
    rewind(input);
}

Linkednode* frequencytable(FILE* file, Linkednode* head, bool* stat) {
    if (file == NULL) {
        return head;
        *stat = false;
    }
    Treenode node;
    int occurences[256] = { 0 };
    char charc;
    int i = 0;
    while ((charc = getc(file)) != EOF) {
        occurences[charc]++;
        i++;
    }
    occurences[0]++;
    for (i = 0; i < 256; i++) {
        if (occurences[i] != 0) {
            node.node.frequency = occurences[i];
            node.node.letter = i;
            node.left = NULL;
            node.parent = NULL;
            node.right = NULL;
            head = insert(head, node, node.node.frequency);
        }
    }
    *stat = true;
    rewind(file);
    return head;
}

Treenode* huffmantree(Treenode* tree, Linkednode* head) {
    while (head->next != NULL) {
        Treenode* x = (Treenode*)malloc(sizeof(Treenode));
        Treenode* y = (Treenode*)malloc(sizeof(Treenode));
        Linkednode* tmp = (Linkednode*)malloc(sizeof(Linkednode));
        head = removeFirst(head, x);
        head = removeFirst(head, y);
        tmp->value.node.frequency = x->node.frequency + y->node.frequency;
        tmp->value.node.letter = '*';
        tmp->value.left = x;
        tmp->value.right = y;
        x->parent = y->parent = &tmp->value;
        head = insert(head, tmp->value, tmp->value.node.frequency);
        tree = &tmp->value;
    }
    tree->parent = NULL;
    return tree;
}

codelist* insertFirst(codelist* head, char letter, int code[], int i) {
    codelist* tmp = (codelist*)malloc(sizeof(codelist));
    tmp->letter = letter;
    tmp->codelength = i;
    tmp->next = NULL;
    int x = 0;
    for (x = 0; x < i; x++) {
        tmp->code[x] = code[x] + '0';
    }
    tmp->code[x] = '\0';
    if (head == NULL) {
        head = tmp;
    } else {
        tmp->next = head;
        head = tmp;
    }
    return head;
}

void GenHuffCodes(Treenode* tree, int arr[], int i) {
    if (tree->left == NULL && tree->right == NULL) {
        head = insertFirst(head, tree->node.letter, arr, i);
    }
    if (tree->right != NULL) {
        arr[i] = 1;
        GenHuffCodes(tree->right, arr, i + 1);
    }
    if (tree->left != NULL) {
        arr[i] = 0;
        GenHuffCodes(tree->left, arr, i + 1);
    }
}

void CodesFile(FILE* output) {
    codelist* tmp = head;
    while (tmp != NULL) {
        fprintf(output, "%c ", tmp->letter);
        fprintf(output, "%s", tmp->code);
        fprintf(output, "\n");
        tmp = tmp->next;
    }
}

int pwr(int x, int y) {
    int total = 1;
    for (int i = 0; i < y; i++) {
        total *= x;
    }
    return total;
}

int getnumberfrombin(char str[]) {
    int pow = 0;
    int total = 0;
    for (int i = 7; i >= 0; i--) {
        total += (int)(str[i] - '0') * pwr(2, pow);
        pow++;
    }
    return total;
}

void reset(char x[], int size) {
    for (int i = 0; i < size; i++) {
        x[i] = '\0';
    }
}

void resetint(int x[], int size) {
    for (int i = 0; i < size; i++) {
        x[i] = 0;
    }
}
