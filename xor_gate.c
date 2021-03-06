// xor_gate.c

#include <stdio.h>
#include "bit_def.h"

Bit xor(Bit a, Bit b) {
    Bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = (a ^ b) & 0x01;

    return r;
}

//test driver
/*int main(void) {
    int a,b;
    for(a = 0; a <= 1; a++)
        for(b = 0; b <= 1; b++)
            printf("%d  XOR  %d  =  %d\n",a, b, xor(a, b));
}*/
