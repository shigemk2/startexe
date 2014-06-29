#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("source nothing\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    char bf[65536];
    int len = fread(bf, 1, sizeof(bf), f);
    fclose(f);

    int mem[30000] = { 0 };
    int curmem = 0;
    int i = 0;
    int nest;

    while( i < len ){
        /* printf("i=%d bf[i]=%c curmem=%d mem[curmem]=%d nest=%d\n", */
        /*        i, bf[i], curmem, mem[curmem], nest); */
        switch(bf[i]) {
        case '+':
            mem[curmem]++;
            break;
        case '-':
            mem[curmem]--;
            break;
        case '>':
            curmem++;
            break;
        case '<':
            curmem--;
            break;
        case '[':
            if (mem[curmem] != 0) break;
            nest = 0;
            while (i < len) {
                if (bf[i] == '[') {
                    nest++;
                } else if (bf[i] == ']') {
                    nest--;
                    if (nest == 0) break;
                }
                i++;
            }
            break;
        case ']':
            if (mem[curmem] == 0) break;
            nest = 0;
            while (i >= 0) {
                if (bf[i] == ']') {
                    nest++;
                } else if (bf[i] == '[') {
                    nest--;
                    if (nest == 0) break;
                }
                i--;
            }
            break;
        case '.':
            putchar(mem[curmem]);
            break;
        case ',':
            mem[curmem] = getchar();
            break;
        }
        i++;
    }
    return 0;
}
