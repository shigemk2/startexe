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
    int i = 0;

    FILE *fw = fopen("translate.c", "wb");
    char incl[] = "#include <stdio.h>\n";
    fwrite(incl, sizeof(incl)-1, 1, fw);

    char charmem[] = "char mem[30000];\n";
    fwrite(charmem, sizeof(charmem)-1, 1, fw);

    char r[] = "int r = 0;;\n";
    fwrite(r, sizeof(r)-1, 1, f);

    char intmain[] = "int main() {;\n";
    fwrite(intmain, sizeof(intmain)-1, 1, fw);
    char Plus[]  = "    mem[r]++;\n";
    char Minus[] = "    mem[r]--;\n";

    while( i < len ){
        switch(bf[i]) {
        case '+':
            fwrite(Plus, sizeof(Plus)-1, 1, fw);
            break;
        case '-':
            fwrite(Minus, sizeof(Minus)-1, 1, fw);
            break;
        case '>':
            break;
        case '<':
            break;
        case '[':
            break;
        case ']':
            break;
        case '.':
            break;
        case ',':
            break;
        }
        i++;
    }

    char pcl[] = "};\n";
    fwrite(pcl, sizeof(pcl)-1, 1, fw);

    fclose(fw);
    return 0;
}
