// not_gate.c

#include <stdio.h>
#include "bit_def.h"

Bit not(Bit a) {
    Bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    r = (~a) & 0x01;

    return r;
}

//test driver
/*int main(void) {
    int a,b;
    for(a = 0; a <= 1; a++)
        printf("NOT %d  =  %d\n",a, not(a));
}*/

