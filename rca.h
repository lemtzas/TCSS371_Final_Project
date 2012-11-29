#ifndef RCA_H
#define RCA_H

#include "bit_def.h"
#include "register.h"

///Mash for Sign bit in a Register
#define SIGN_BIT_MASK 0x8000

///Utility that checks a single bit of a register
Bit getBit(Register R, Register pos);
///Utility to set a single bit of a register
Register setBit(Register R, Register pos, Bit bit);


//Unused structure from sample text (were we required to use this? It didn't seem necessary)
/*typedef struct {
	Bit a;
	Bit b;
	Bit c_in;
	Bit r;
	Bit c_out;
} FullAdder;

typedef FullAdder * FullAdderPtr;*/

///full adder utility
Bit fullAdder (Bit a, Bit b, Bit c_in, Bit *c_out);
//------------------------------------------------------------------------------------------------------
///Ripple Carry Adder Object
typedef struct {
	//FullAdder adders[16]; // or #define number of adders //(I did not require this, was it necessary?)
	Register A, B, R;
	unsigned char flags; // flags[0]=O, flags[1]=C, flags[2]=Z, flags[3]=N  NZCO
	// any other housekeeping variables?
} RippleCarryAdder;

typedef RippleCarryAdder * RippleCarryAdderPtr;

//ripple carry adder prototypes
int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, Register A, Register B);
int rippleCarryAdderAdd(RippleCarryAdderPtr this); // returns error code if a problem occurred
unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr, int * error);  // error is an integer for error codes
unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error);
// any other methods deemed necessary to work with this object

#endif
