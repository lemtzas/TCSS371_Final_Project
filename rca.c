//#define DEBUG
//#define DEBUG_V

#include "rca.h"
#include "or_gate.h"
#include "xor_gate.h"
#include "and_gate.h"



///full adder
//I did not require any structs for this
//I'm not sure if it was required that we use a struct for it
Bit fullAdder (Bit a, Bit b, Bit c_in, Bit * c_out)
{
    //the two xor gate model
    Bit xor_ab  = xor(a,b);
    Bit res     = xor(c_in, xor_ab);

    Bit and_cab = and(xor_ab,c_in);
    Bit and_ab  = and(a,b);

    *c_out  = or(and_cab,and_ab);
    return res;
}

///setup a ripple carry adder
int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, Register A, Register B)
{
    this->A = (Register) A;
    this->B = (Register) B;
    return 0;   //error code?
}

///perform the ripple carry add operation (requires the registers to be set by ripple carry adder)
int rippleCarryAdderAdd(RippleCarryAdderPtr this)
{
    ///reset registers
    this->R = 0x0000;   //clear output register
    this->flags = 0;    //clear flags

    ///perform addition
    int i;                  //the current bit (from right)
    Bit o = 0b0;            //output of carry
    Bit c = 0b0;            //carry bit (in)
    Bit co = 0b0;           //carry bit (out)
    for(i=0; i < 16; i++)
    {
        o = fullAdder(getBit(this->A,i), getBit(this->B,i), c, &co);
        #ifdef DEBUG_V
        printf("%d + %d (c%d) = %d (c%d) | %4x %d\n", getBit(this->A,i), getBit(this->B,i), c, o, co, this->R, this->R);
        #endif
        c = co;
        this->R = setBit(this->R,i,o);
    }

    ///flag interpretations
    //N - flags[3] - negative test
    if(getBit(this->R,15))
        this->flags = setBit(0x0,3,1);
    //Z - flags[2] - zero test
    Bit z = 0;
    for(i=0; i < 16; i++)
        z = or(z, getBit(this->R,i));
    if(!z)
        this->flags = setBit(0x0,2,1);
    //C - flags[1] - carry test
    if(co)
        this->flags = setBit(this->flags,1,1);
    //O - flags[0] - overflow test
    #ifdef DEBUG
    printf("A | B | R\n%d   %d   %d\n", getBit(this->A,15), getBit(this->B,15), getBit(this->R,15));
    #endif
    if(   ((getBit(this->A,15) && getBit(this->B,15)) && !getBit(this->R,15))
       || ((!getBit(this->A,15) && !getBit(this->B,15)) && getBit(this->R,15))) {
        this->flags = setBit(this->flags,0,1);
    }

    return 0;   //error code?
}

///Tells you the result of a ripple carry add after you have performed rippleCarryAdderAdd
unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr this, int * error)
{
    //not used...yet
    if( error ) (*error) = 0;
    return (unsigned short)this->R;
}

///Tells you the state of the flags after you have performed rippleCarryAdderAdd
unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error)
{
    //not used...yet
    if( error ) (*error) = 0;
    return this->flags;
}








///Utility that returns a single bit of a register
Bit getBit(Register R, Register pos) {
    return maskBit(R >> pos);
}

///Utility to set a single bit of a register
Register setBit(Register R, Register pos, Bit bit) {
    Register mask = 0x0001 << pos;
    if( bit )
        return R | mask;
    else
        return R & ~mask;
}


/**
 * Test drivers
 */


/*
int main()
{
    fullAdderTest();
    printf("============================\n");
    rippleCarryAdderTest();
    return 0;
}

///Prints all combinations of the fullAdder function, easily verified by hand
void fullAdderTest()
{
    Bit a;
    Bit b;
    Bit c;
    Bit o;
    Bit co;
    for(a = 0; a <= 1; a++) {
        for(b = 0; b <= 1; b++) {
            for(c = 0; c <= 1; c++) {
                o = fullAdder(a,b,c,&co);
                printf("%d + %d (C%d) = %d (%d)\n", a, b, c, o, co);
            }
        }
    }
}

///Prints the results of a few strategic tests of the rippleCarryAdder ADT, easily verified by hand
void rippleCarryAdderTest() {
    rcaTest(0x0022,0x0122);
    rcaTest(0x70B0,0x41AA); //0xB25A with overflow, but no carry (ends up negative)
    rcaTest(0xA123,0x8001); //0x2124 with carry and overflow
    rcaTest(0xA123,0x7001); //0x1124 with carry, no overflow
    //my tests
    rcaTest(0x0000,0x0000); //0x0000 zero result without carry or overflow
    rcaTest(0xF000,0x0FFF); //0xFFFF negative result without carry or overflow
}

void rcaTest(unsigned short A, unsigned short B)
{
    //acquire space for operations
    RippleCarryAdderPtr rca = malloc(sizeof(RippleCarryAdder));
    //set registers
    rippleCarryAdderSetRegisters(rca,A,B);
    //perform operation
    rippleCarryAdderAdd(rca);
    //view results (A + B = C + flags)
    printf("0x%04X + 0x%04X = 0x%04X flags 0x%X\n", A, B, rippleCarryAdderGetResult(rca,0), rippleCarryAdderGetFlags(rca,0));
}
*/
