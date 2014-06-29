#include <stdio.h>

int main(void) {
    FILE *f = fopen("test.b", "rb");
    int c;
    fgetc(f);
    int reg[8];
    reg[0] = 0;
    int curreg = 0;

    while( (c = fgetc( f )) != EOF ){
        /* printf( "%c", c ); */
        if (c == '+') {
            reg[curreg] += 1;
        }
        if (c == '-') {
            reg[curreg] -= 1;
        }
        if (c == '>') {
            curreg += 1;
        }
        if (c == '<') {
            curreg -= 1;
        }
        if (c == '.') {
            printf( "%d", reg[curreg]);
            printf( "%c", reg[curreg]);
        }
    }
    printf( "%d\n", reg[0]);
    printf( "%c\n", reg[0]);

    fclose(f);
    return 0;
}
