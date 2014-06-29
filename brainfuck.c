#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("source nothing\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    char bf[65536];
    int c;
    fgetc(f);
    int mem[8] = { 0 };
    int curmem = 0;
    int i = 0;
    int tojikakko = 1;
    int start = 0;

    int len = fread(bf, 1, sizeof(bf), f);
    while( i <= sizeof(bf) ){
        switch(bf[i]) {
        case '+':
            mem[curmem] += 1;
            break;
        case '-':
            mem[curmem] -= 1;
            break;
        case '>':
            curmem += 1;
            break;
        case '<':
            curmem -= 1;
            break;
        case '[':
            start = i;
            break;
        case ']':
            if (mem[0]<0) break;
            i--;
            while (tojikakko > 0) {
                if (bf[i] == ']') {
                    tojikakko++;
                } else if (bf[i] == '[') {
                    tojikakko--;
                }
                i--;
                start = i;
            }
            i = start;
            break;
        case '.':
            printf( "%c", mem[curmem]);
            break;
        case ' ':
        case '\n':
            break;
        default :
            i = sizeof(bf) + 1;
            break;
        }
        i++;
    }
    fclose(f);
    return 0;
}
