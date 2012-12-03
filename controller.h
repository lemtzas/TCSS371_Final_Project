#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "register.h"
#include "registers.h"
#include "alu.h"
#include "memory.h"
#include "not_gate.h"
#include "or_gate.h"
#include "and_gate.h"

//0b0001
#define OPCODE_ADD  0x1
//0b0101
#define OPCODE_AND  0x5
//0b1101
#define OPCODE_SUB  0xD

//0b1001
#define OPCODE_NOT  0x9

//0b0000
#define OPCODE_BR   0x0
//0b1100
#define OPCODE_JMP  0xC

//0b0010
#define OPCODE_LD   0x2
//0b0110
#define OPCODE_LDR  0x6
//0b1110
#define OPCODE_LEA  0xE

//0b0011
#define OPCODE_ST   0x3
//0b0111
#define OPCODE_STR  0x7

//0b1000
#define OPCODE_HALT 0x8

typedef struct {
    Bit halt;
} Controller;

//char* error_string alu_run_step(Controller *controller, ALU *alu, Registers *registers, Memory *memory)
char* controller_initialize(Controller *this);

//char* error_string alu_run_step(Controller *controller, ALU *alu, Registers *registers, Memory *memory)
char* controller_run_step(Controller *this, ALU *alu, Registers *registers, Memory *memory);

//sign extends something of length /bits/ to the length of a full register
Register _controller_util_sext(Register in, unsigned short bits);
//sets the PSR as appropriate
void _controller_util_setcc(Controller *this,PSR *psr,Register value);

///OPCODE
typedef struct {
    unsigned short junk:12;
    unsigned short code:4;
} _DATAMASK_OPCODE; //i

///ADD
typedef struct {
    unsigned short sr2:3;
    unsigned short zeros:3;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_ADD_REGS; //i

typedef struct {
    signed short imm5:5;     //signed for bit extend?
    unsigned short one:1;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_ADD_IMM5; //i

///AND
typedef struct {
    unsigned short sr2:3;
    unsigned short zeros:3;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_AND_REGS; //i

typedef struct {
    signed short imm5:5;     //signed for bit extend?
    unsigned short one:1;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_AND_IMM5; //i

///SUB
typedef struct {
    unsigned short sr2:3;
    unsigned short zeros:3;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_SUB_REGS; //i

typedef struct {
    signed short imm5:5;     //signed for bit extend?
    unsigned short one:1;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_SUB_IMM5; //i

///NOT
typedef struct {
    unsigned short ones:6;
    unsigned short sr1:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_NOT; //i

///HALT
typedef struct {
    unsigned short zeros:12;
    unsigned short code:4;
} _DATAMASK_HALT;

///JMP
typedef struct {
    unsigned short zeros2:6;
    unsigned short baser:3;
    unsigned short zeros:3;
    unsigned short code:4;
} _DATAMASK_JMP; //i

///BR
typedef struct {
    signed short pcoffset7:7;
    unsigned short p:1;
    unsigned short z:1;
    unsigned short n:1;
    unsigned short o:1;
    unsigned short c:1;
    unsigned short code:4;
} _DATAMASK_BR; //i

///LDs
typedef struct {
    unsigned short pcoffset9:9;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_LD; //i

typedef struct {
    unsigned short pcoffset6:6;
    unsigned short baser:3;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_LDR; //i

typedef struct {
    unsigned short pcoffset9:9;
    unsigned short dr:3;
    unsigned short code:4;
} _DATAMASK_LEA; //i

///STs
typedef struct {
    unsigned short pcoffset9:9;
    unsigned short sr:3;
    unsigned short code:4;
} _DATAMASK_ST; //i

typedef struct {
    unsigned short pcoffset6:6;
    unsigned short baser:3;
    unsigned short sr:3;
    unsigned short code:4;
} _DATAMASK_STR; //i



typedef struct {
    _DATAMASK_OPCODE opcode;

    _DATAMASK_ADD_REGS add_regs;
    _DATAMASK_ADD_IMM5 add_imm5;

    _DATAMASK_AND_REGS and_regs;
    _DATAMASK_AND_IMM5 and_imm5;

    _DATAMASK_SUB_REGS sub_regs;
    _DATAMASK_SUB_IMM5 sub_imm5;

    _DATAMASK_NOT not;

    _DATAMASK_BR br;
    _DATAMASK_JMP jmp;

    _DATAMASK_LD ld;
    _DATAMASK_LDR ldr;
    _DATAMASK_LEA lea;

    _DATAMASK_ST st;
    _DATAMASK_STR str;

    _DATAMASK_HALT halt;
} _DATAMASKS;


#endif
