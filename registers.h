#ifndef REGISTERS_H
#define REGISTERS_H

#include "register.h"

#define REG_R0  0
#define REG_R1  1
#define REG_R2  2
#define REG_R3  3
#define REG_R4  4
#define REG_R5  5
#define REG_R6  6
#define REG_R7  7

#define REG_IR  8
#define REG_PC  9

#define REG_MAR 10
#define REG_MDR 11

#define REG_PSR 12

typedef struct {

} Registers;

//char* error_string registers_initialize( Registers *registers )
char* registers_initialize( Registers *registers );
//char* error_string registers_get_register(  Registers *registers , Register *register_out , unsigned short REGISTER_ID )
char* registers_get_register( Registers *registers , Register *register_out , unsigned short REGISTER_ID );
//char* error_string registers_set_register(  Registers *registers , Register *register_out , unsigned short REGISTER_ID )
char* registers_set_register( Registers *registers , Register register_in , unsigned short REGISTER_ID );

#endif
