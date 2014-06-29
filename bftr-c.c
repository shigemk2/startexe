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

    char plus[]     = "    /* + */ mem[r]++;\n";
    char minus[]    = "    /* - */ mem[r]--;\n";
    char whileo[]   = "    /* [ */ while (mem[r]) {\n";
    char whilec[]   = "    /* ] */ };\n";
    char memplus[]  = "    /* > */ r++;\n";
    char memminus[] = "    /* < */ r--;\n";
    char pchar[]    = "    /* . */ putchar(mem[r]);\n";
    char return0[]  = "    return 0;\n";

    while( i < len ){
        switch(bf[i]) {
        case '+':
            fwrite(plus, sizeof(plus)-1, 1, fw);
            break;
        case '-':
            fwrite(minus, sizeof(minus)-1, 1, fw);
            break;
        case '>':
            fwrite(memplus, sizeof(memplus)-1, 1, fw);
            break;
        case '<':
            fwrite(memminus, sizeof(memminus)-1, 1, fw);
            break;
        case '[':
            fwrite(whileo, sizeof(whileo)-1, 1, fw);
            break;
        case ']':
            fwrite(whilec, sizeof(whilec)-1, 1, fw);
            break;
        case '.':
            fwrite(pchar, sizeof(pchar)-1, 1, fw);
            break;
        case ',':
            break;
        }
        i++;
    }

    fwrite(return0, sizeof(return0)-1, 1, fw);

    char pcl[] = "};\n";
    fwrite(pcl, sizeof(pcl)-1, 1, fw);

    fclose(fw);
    return 0;
}
