#ifndef ALU_H
#define ALU_H

#include "rca.h"
#include "register.h"
#include "psr.h"

///OO storage
typedef struct {
	Register r[8];
    Register src1;
    Register src2;
    Register result;
} ALU;


///operations
//performs the designated operation on the operands in the alu
//the state of src1 and src2 is undefined after an ALU_operation is completed
//errors are returned as strings, if an exist (I think I'll go back and do this with all my Objects)

//negation operation. Nots and Increments src1. Sets the same PSR flags as ADD.
char* ALU_operation_neg(ALU* this, PSR* psr);
//add operation. Uses the Ripple Carry Adder. Sets NZCO flags in PSR.
char* ALU_operation_add(ALU* this, PSR* psr);
//subtraction operation. negates src2. Sets the same PSR flags as ADD.
char* ALU_operation_sub(ALU* this, PSR* psr);
//bitwise and operation. combines src1 and src2 via "and" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_and(ALU* this, PSR* psr);
//bitwise or operation. combines src1 and src2 via "or" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_or(ALU* this, PSR* psr);
//bitwise not operation. combines src1 and src2 via "not" operation. Sets NZ, clears CO in PSR.
char* ALU_operation_not(ALU* this, PSR* psr);

///operand + result access
//sets the value of src1; use before each ALU_operation
char* ALU_set_src1(ALU* this, Register src1);
//sets the value of src2; use before each ALU_operation
char* ALU_set_src2(ALU* this, Register src2);
//retreives the result value; use after ALU_operation
char* ALU_get_result(ALU* this, Register *result);

#endif
