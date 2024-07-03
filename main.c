#include "huffman.h"

int main() {
    clock_t begin, end1, end2;
    FILE* input;
    FILE* codes;
    FILE* output;
    bool status;
    Linkednode* n = NULL;
    Treenode* hufftree = NULL;
    int original = 0;
    int sentence[64];
    char charc;
    int i = 0;
    bool compress = false;
    int arr[100] = { 0 };
    double time_spent;
    int extrabits;
    int j = 0;
    char letter = 0;
    codelist* h = NULL;
    fopen_s(&input, "input.txt", "rb");
    fopen_s(&codes, "codes.dat", "wb");
    fopen_s(&output, "output.dat", "wb");
    bool Event = true;
    printf("The Input File Has %d Characters\nPress '1' To Begin The Compression\nPress '2' To Calculate The Compression Ratio\nPress '3' To Begin The Decompression\nPress Q To Exit\n", getfile(input));
    char Choice;
    while (Event) {
        Choice = _getch();
        switch (Choice) {
            case '1':
                if (compress == false) {
                    begin = clock();
                    printf("Starting The Compression...\n");
                    n = frequencytable(input, n, &status);
                    if (status == true) {
                        printf("The Frequency Table Has Been Created Successfully!\n");
                    }
                    hufftree = huffmantree(hufftree, n);
                    printf("The Huffman Tree Has Been Created Successfully!\n");
                    GenHuffCodes(hufftree, arr, 0);
                    CodesFile(codes);
                    printf("The Codes Have Been Generated Successfully! And Was Inserted In codes.dat\n");
                    printf("Beginning Compression!!\n");
                    while ((charc = getc(input)) != EOF) {
                        sentence[i] = charc;
                        i++;
                        original++;
                        if (i == 64) {
                            Compress(output, sentence, 64, false);
                            resetint(sentence, i);
                            i = 0;
                        }
                    }
                    sentence[i++] = '\0';
                    Compress(output, sentence, i, true);
                    end1 = clock();
                    time_spent = ((double)end1 - begin) / CLOCKS_PER_SEC;
                    printf("The File Has Been Compressed In %lf Seconds And Now Has %d Characters\n", time_spent, getfile(output));
                    fclose(input);
                    fclose(output);
                    fclose(codes);
                    compress = true;
                } else {
                    printf("File Already Compressed!\n");
                }
                break;
            case '2':
                if (compress == false) {
                    printf("To Calculate The Ratio You Need To Compress First.\n");
                } else {
                    calcRatio(original);
                }
                break;
            case '3':
                if (compress == false) {
                    printf("To Decompress You Need To Compress First.\n");
                } else {
                    begin = clock();
                    printf("\nBeginning The Decompression: \n");
                    FILE* outp;
                    fopen_s(&outp, "output.dat", "rb");
                    FILE* code;
                    fopen_s(&code, "codes.dat", "rb");
                    int geh = getfile(outp) - 2;
                    int out[64];
                    i = 0;
                    while ((charc = getc(code)) != EOF) {
                        letter = charc;
                        while ((charc = getc(code)) != '\n') {
                            if (charc != ' ') {
                                arr[i] = charc - '0';
                                i++;
                                arr[i] = '\0';
                            }
                        }
                        h = insertFirst(h, letter, arr, i);
                        i = 0;
                    }
                    fclose(code);
                    for (i = 0; i < geh; i++) {
                        charc = getc(outp);
                        out[j] = (int)charc;
                        j++;
                        if (j == 64) {
                            decompress(h, 64, out, 0, false);
                            j = 0;
                        }
                    }
                    fscanf_s(outp, "\n%d", &extrabits);
                    decompress(h, j, out, extrabits, true);
                    fclose(output);
                    end2 = clock();
                    time_spent = ((double)end2 - begin) / CLOCKS_PER_SEC;
                    printf("\nDecompression Completed in %lf Seconds!\n", time_spent);
                    printf("To Exit Press Q.\n");
                }
                break;
            case 'Q':
            case 'q':
                Event = false;
                break;
            default:
                printf("To Exit Press Q\n");
        }
    }
    return 0;
}
