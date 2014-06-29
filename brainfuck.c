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
    int reg[8];
    reg[0] = 0;
    int curreg = 0;
    int i = 0;
    int start = 0;

    int len = fread(bf, 1, sizeof(bf), f);
    while( i <= sizeof(bf) ){
        switch(bf[i]) {
        case '+':
            reg[curreg] += 1;
            break;
        case '-':
            reg[curreg] -= 1;
            break;
        case '>':
            curreg += 1;
            break;
        case '<':
            curreg -= 1;
            break;
        case '[':
            start = i;
            break;
        case ']':
            if (reg[0] >= 0) {
                i = start;
            }
            break;
        case '.':
            printf( "%c", reg[curreg]);
            break;
        case ' ':
        case '\n':
            break;
        default :
            i = sizeof(bf) + 1;
            break;
        }
        i += 1;
    }
    fclose(f);
    return 0;
}
