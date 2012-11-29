// nand_gate.c

#include <stdio.h>
#include "bit_def.h"
#include "and_gate.h"
#include "not_gate.h"

Bit nand(Bit a, Bit b) {
    Bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = not(and(a,b)) & 0x01;

    return r;
}

//test driver
/*int main(void) {
    int a,b;
    for(a = 0; a <= 1; a++)
        for(b = 0; b <= 1; b++)
            printf("%d  NAND  %d  =  %d\n",a, b, nand(a, b));
}*/
