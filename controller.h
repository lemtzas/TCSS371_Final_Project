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
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_OPCODE;

///ADD
typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short zeros:3;
    unsigned short sr2:3;
} _DATAMASK_ADD_REGS;

typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short one:1;
    signed short imm5:5;     //signed for bit extend?
} _DATAMASK_ADD_IMM5;

///AND
typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short zeros:3;
    unsigned short sr2:3;
} _DATAMASK_AND_REGS;

typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short one:1;
    signed short imm5:5;     //signed for bit extend?
} _DATAMASK_AND_IMM5;

///SUB
typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short zeros:3;
    unsigned short sr2:3;
} _DATAMASK_SUB_REGS;

typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short one:1;
    signed short imm5:5;     //signed for bit extend?
} _DATAMASK_SUB_IMM5;

///NOT
typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short sr1:3;
    unsigned short ones:6;
} _DATAMASK_NOT;

///HALT
typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_HALT;

///JMP
typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_JMP;

///BR
typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_BR;

///LDs
typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_LD;

typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_LDR;

typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_LEA;

///STs
typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_ST;

typedef struct {
    unsigned short code:4;
    unsigned short junk:12;
} _DATAMASK_STR;


#endif
