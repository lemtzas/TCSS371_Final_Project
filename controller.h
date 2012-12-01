#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "register.h"
#include "registers.h"
#include "alu.h"
#include "memory.h"

typedef struct {

} Controller;

//char* error_string alu_run_step(Controller *controller, ALU *alu, Registers *registers, Memory *memory)
char* controller_run_step(Controller *this, ALU *alu, Registers *registers, Memory *memory);



///OPCODE
typedef struct {

} _DATAMASK_OPCODE;

///ADD
typedef struct {

} _DATAMASK_ADD_REGS;

typedef struct {

} _DATAMASK_ADD_IMM5;

///AND
typedef struct {

} _DATAMASK_AND_REGS;

typedef struct {

} _DATAMASK_AND_IMM5;

///SUB
typedef struct {

} _DATAMASK_SUB_REGS;

typedef struct {

} _DATAMASK_SUB_IMM5;

///NOT
typedef struct {

} _DATAMASK_NOT;

///HALT
typedef struct {

} _DATAMASK_HALT;

///JMP
typedef struct {

} _DATAMASK_JMP;

///BR
typedef struct {

} _DATAMASK_BR;

///LDs
typedef struct {

} _DATAMASK_LD;

typedef struct {

} _DATAMASK_LDR;

typedef struct {

} _DATAMASK_LEA;

///STs
typedef struct {

} _DATAMASK_ST;

typedef struct {

} _DATAMASK_STR;


#endif
