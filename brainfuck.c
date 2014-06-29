#include <stdio.h>

int main(void) {
    FILE *f = fopen("test.b", "r");
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
        if (bf[i] == '+') {
            reg[curreg] += 1;
        }
        if (bf[i] == '-') {
            reg[curreg] -= 1;
        }
        if (bf[i] == '>') {
            curreg += 1;
        }
        if (bf[i] == '<') {
            curreg -= 1;
        }
        if (bf[i] == '[') {
            start = i;
        }
        if (bf[i] == ']') {
            i = start;
        }
        if (bf[i] == '.') {
            printf( "%c", reg[curreg]);
            return 0;
        }
        i += 1;
    }
    fclose(f);
    return 0;
}
