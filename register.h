#ifndef REGISTER_H
#define REGISTER_H

#include "bit_def.h"

///Register simulation
typedef unsigned short Register;


//void registerInitialize(); unnecessary?

//sets a register's value (via unsigned short)
char* register_set(Register* this, unsigned short value);
//retrieves a register's value (unto an unsigned short)
char* register_get(Register* this, unsigned short* result);
//retrieves the value for a specific bit in a register, returns error string if invalid pos
char* register_get_bit(Register* this,int pos,Bit* result);
//sets the value for a specific bit in a register, returns error string if invalid pos
char* register_set_bit(Register* this,int pos,Bit state);

#endif
