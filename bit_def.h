//bit_def.h
//I added a header guard
#ifndef BIT_DEF
#define BIT_DEF

typedef unsigned char Bit;        // simulates a single Bit, we'll use the low order Bit in a byte

#ifndef BIT0_MASK
#define BIT0_MASK 0x01
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

Bit maskBit(Bit);    // used to ensure only Bit 0 has a non-zero value

#endif
