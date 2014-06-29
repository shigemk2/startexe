#include <stdio.h>

int main(void) {
    FILE *f = fopen("test.b", "rb");
    int c;
    fgetc(f);

    while( (c = fgetc( f )) != EOF ){
        printf( "%c", c );
    }

    fclose(f);
    return 0;
}
