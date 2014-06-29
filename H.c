#include <stdio.h>

char mem[30000];
int r = 0;

int main() {
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* [ */ while (mem[r]) {
    /* > */ r++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* + */ mem[r]++;
    /* < */ r--;
    /* - */ mem[r]--;
    /* ] */ }
    /* > */ r++;
    /* . */ putchar(mem[r]);
    return 0;
}

