#include "alu.h"
#include "register.h"
#include "bit_def.h"
#include "and_gate.h"
#include "or_gate.h"
#include "not_gate.h"
#include "rca.h"
#include "psr.h"

///operations
//performs the designated operation on the operands in the alu
//the state of src1 and src2 is undefined after an ALU_operation is completed

//negation operation. Nots and Increments src1. Sets the same PSR flags as ADD.
char* ALU_operation_neg(ALU* this,PSR* psr)
{
    //negate
    ALU_operation_not(this,psr);

    //alter srcs to increment for ease
    ALU_set_src1(this,this->result);
    ALU_set_src2(this,1);

    //add one, also sets PSR
    ALU_operation_add(this,psr);

    return 0; //no errors
}

//add operation. Uses the Ripple Carry Adder. Sets NZCO flags in PSR.
char* ALU_operation_add(ALU* this,PSR* psr)
{
    //perform the addition with the ripple carry adder
    RippleCarryAdder rca;
    rippleCarryAdderSetRegisters(&rca,this->src1,this->src2);
    rippleCarryAdderAdd(&rca);
    this->result = rippleCarryAdderGetResult(&rca,0);
    unsigned char flags = rippleCarryAdderGetFlags(&rca,0);
    //interpret the flags
    Bit n = (flags>>3)&0b1;
    Bit z = (flags>>2)&0b1;
    Bit c = (flags>>1)&0b1;
    Bit o = (flags)&0b1;
    //set them if we were given an psr
    if(psr) PSR_set_nzco(psr,n,z,c,o);

    return 0; //no errors?
}

//subtraction operation. negates src2. Sets the same PSR flags as ADD.
char* ALU_operation_sub(ALU* this,PSR* psr)
{
    Register temp = this->src1;  //store src1 so we can use NEG (for ease)
    this->src1 = this->src2;     //copy src2 into src1 to negate it (we need src2 negged so we can calc src1 - src2)
    ALU_operation_neg(this,psr); //negate src1 (now src2)
    this->src2 = this->result;   //copy result into src2
    this->src1 = temp;           //reload src1 to its original value
    ALU_operation_add(this,psr); //final addition operation
    return 0; //no errors
}

//bitwise and operation. combines src1 and src2 via "and" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_and(ALU* this,PSR* psr)
{
    int i;
    Bit a; //a
    Bit b; //b
    Bit r; //result
    Bit z = 1; //zero flag, starts as 1, gets cleared if any bit is not 0
    Bit n = 0; //negative flag
    for(i = 0;i<16;i++) //all bits in reg
    {
        register_get_bit(&(this->src1),i,&a);
        register_get_bit(&(this->src2),i,&b);
        r = and(a,b);
        register_set_bit(&(this->result),i,r);
        if(r) z = 0; //clear zero flag if non-zero
    }
    //check if negative, set flag accordingly
    register_get_bit(&(this->result),15,&r);
    if(r) n = 1;
    if(psr) PSR_set_nzco(psr,n,z,0,0);
    return 0;
}

//bitwise or operation. combines src1 and src2 via "or" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_or(ALU* this,PSR* psr)
{
    int i;
    Bit a; //a
    Bit b; //b
    Bit r; //result
    Bit z = 1; //zero flag, starts as 1, gets cleared if any bit is not 0
    Bit n = 0; //negative flag
    for(i = 0;i<16;i++) //all bits in reg
    {
        register_get_bit(&(this->src1),i,&a);
        register_get_bit(&(this->src2),i,&b);
        r = or(a,b);
        register_set_bit(&(this->result),i,r);
        if(r) z = 0; //clear zero flag if non-zero
    }
    //check if negative, set flag accordingly
    register_get_bit(&(this->result),15,&r);
    if(r) n = 1;
    if(psr) PSR_set_nzco(psr,n,z,0,0);
    return 0;
}
//bitwise not operation. combines src1 and src2 via "not" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_not(ALU* this,PSR* psr)
{
    int i;
    Bit a; //a
    Bit r; //result
    Bit z = 1; //zero flag, starts as 1, gets cleared if any bit is not 0
    Bit n = 0; //negative flag
    for(i = 0;i<16;i++) //all bits in reg
    {
        register_get_bit(&(this->src1),i,&a);
        r = not(a);
        register_set_bit(&(this->result),i,r);
        if(r) z = 0; //clear zero flag if non-zero
    }
    //check if negative, set flag accordingly
    register_get_bit(&(this->result),15,&r);
    if(r) n = 1;
    if(psr) PSR_set_nzco(psr,n,z,0,0); //set flags
    return 0;
}

///operand + result access
//sets the value of src1; use before each ALU_operation
char* ALU_set_src1(ALU* this, Register src1)
{
    this->src1 = src1;
    return 0; //no errors
}

//sets the value of src2; use before each ALU_operation
char* ALU_set_src2(ALU* this, Register src2)
{
    this->src2 = src2;
    return 0;
}

//retreives the result value; use after ALU_operation
char* ALU_get_result(ALU* this, Register *result)
{
    (*result) = this->result;
    return 0;
}


//simple test driver for alu
//int main()
//{
//    ALU alu;
//    Register r0;
//    Register r1;
//    Register r2;
//    Register r3;
//
//    //add
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0x0001);
//    ALU_operation_add(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("add %04x, %04x -> %04x\n", 0xFFFF, 0x0001, r1);
//    ALU_set_src1(&alu,0x1010);
//    ALU_set_src2(&alu,0x0808);
//    ALU_operation_add(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("add %04x, %04x -> %04x\n", 0x1010, 0x0808, r1);
//
//
//    //sub (neg can be assumed correct if this is correct)
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0x0001);
//    ALU_operation_sub(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("sub %04x, %04x -> %04x\n", 0xFFFF, 0x0001, r1);
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0xFFFF);
//    ALU_operation_sub(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("sub %04x, %04x -> %04x\n", 0xFFFF, 0xFFFF, r1);
//    ALU_set_src1(&alu,0x0000);
//    ALU_set_src2(&alu,0x0001);
//    ALU_operation_sub(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("sub %04x, %04x -> %04x\n", 0x0000, 0x0001, r1);
//
//
//    //not
//    ALU_set_src1(&alu,0x0000);
//    ALU_operation_not(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("not %04x -> %04x\n", 0x0000, r1);
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_operation_not(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("not %04x -> %04x\n", 0xFFFF, r1);
//    ALU_set_src1(&alu,0x1010);
//    ALU_operation_not(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("not %04x -> %04x\n", 0x1010, r1);
//    ALU_set_src1(&alu,0xF0F0);
//    ALU_operation_not(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("not %04x -> %04x\n", 0xF0F0, r1);
//    ALU_set_src1(&alu,0x7FF7);
//    ALU_operation_not(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("not %04x -> %04x\n", 0x7FF7, r1);
//
//
//    //and
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0xFFFF);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0xFFFF, 0xFFFF, r1);
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0x187E);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0xFFFF, 0x187E, r1);
//    ALU_set_src1(&alu,0x187E);
//    ALU_set_src2(&alu,0xFFFF);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0x187E, 0xFFFF, r1);
//    ALU_set_src1(&alu,0x187E);
//    ALU_set_src2(&alu,0x0000);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0x187E, 0x0000, r1);
//    ALU_set_src1(&alu,0xF0F0);
//    ALU_set_src2(&alu,0x0F0F);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0xF0F0, 0x0F0F, r1);
//    ALU_set_src1(&alu,0xF0F0);
//    ALU_set_src2(&alu,0xF0F0);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0xF0F0, 0xF0F0, r1);
//    ALU_set_src1(&alu,0x1818);
//    ALU_set_src2(&alu,0x8181);
//    ALU_operation_and(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("and %04x, %04x -> %04x\n", 0x1818, 0x8181, r1);
//
//
//
//
//
//
//    //or
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0xFFFF);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0xFFFF, 0xFFFF, r1);
//    ALU_set_src1(&alu,0xFFFF);
//    ALU_set_src2(&alu,0x187E);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0xFFFF, 0x187E, r1);
//    ALU_set_src1(&alu,0x187E);
//    ALU_set_src2(&alu,0xFFFF);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0x187E, 0xFFFF, r1);
//    ALU_set_src1(&alu,0x187E);
//    ALU_set_src2(&alu,0x0000);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0x187E, 0x0000, r1);
//    ALU_set_src1(&alu,0x0000);
//    ALU_set_src2(&alu,0x0000);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0x0000, 0x0000, r1);
//    ALU_set_src1(&alu,0xF0F0);
//    ALU_set_src2(&alu,0x0F0F);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0xF0F0, 0x0F0F, r1);
//    ALU_set_src1(&alu,0xF0F0);
//    ALU_set_src2(&alu,0xF0F0);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0xF0F0, 0xF0F0, r1);
//    ALU_set_src1(&alu,0x1818);
//    ALU_set_src2(&alu,0x8181);
//    ALU_operation_or(&alu,0);
//    ALU_get_result(&alu,&r1);
//    printf("or  %04x, %04x -> %04x\n", 0x1818, 0x8181, r1);
//
//
//
//
//    return 0;
//}
