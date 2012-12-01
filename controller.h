#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "register.h"
#include "registers.h"
#include "alu.h"
#include "memory.h"

#define OPCODE_ADD  0b0001
#define OPCODE_AND  0b0101
#define OPCODE_SUB  0b1101

#define OPCODE_NOT  0b1001

#define OPCODE_BR   0b0000
#define OPCODE_JMP  0b1100

#define OPCODE_LD   0b0010
#define OPCODE_LDR  0b0110
#define OPCODE_LEA  0b1110

#define OPCODE_ST   0b0011
#define OPCODE_STR  0b0111

#define OPCODE_HALT 0b1000

typedef struct {

} Controller;

//char* error_string alu_run_step(Controller *controller, ALU *alu, Registers *registers, Memory *memory)
char* controller_run_step(Controller *this, ALU *alu, Registers *registers, Memory *memory);

//sign extends something of length /bits/ to the length of a full register
Register _controller_util_sext(Register in, unsigned short bits);

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
    unsigned short zeros:12;
} _DATAMASK_HALT;

///JMP
typedef struct {
    unsigned short code:4;
    unsigned short c:1;
    unsigned short o:1;
    unsigned short n:1;
    unsigned short z:1;
    unsigned short p:1;
    signed short pcoffset7:7;
} _DATAMASK_JMP;

///BR
typedef struct {
    unsigned short code:4;
    unsigned short zeros:3;
    unsigned short baser:3;
    unsigned short zeros2:6;
} _DATAMASK_BR;

///LDs
typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short pcoffset9:9;
} _DATAMASK_LD;

typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short baser:3;
    unsigned short pcoffset6:6;
} _DATAMASK_LDR;

typedef struct {
    unsigned short code:4;
    unsigned short dr:3;
    unsigned short pcoffset9:9;
} _DATAMASK_LEA;

///STs
typedef struct {
    unsigned short code:4;
    unsigned short sr:3;
    unsigned short pcoffset9:9;
} _DATAMASK_ST;

typedef struct {
    unsigned short code:4;
    unsigned short sr:3;
    unsigned short baser:3;
    unsigned short pcoffset6:6;
} _DATAMASK_STR;



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
