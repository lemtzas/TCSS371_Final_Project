#include "controller.h"

char* controller_run_step(Controller *this, ALU *alu, Registers *registers, Memory *memory)
{
    Register temp;
    Register ir;
    Register pc;
    ///FETCH
    //MAR <- PC
    registers_get_register(registers,&pc,REG_PC);
    registers_set_register(registers,pc,REG_MAR);

    //PC <- PC + 1
    registers_set_register(registers,++pc,REG_PC);

    //LOAD MEMORY
    memory_get(memory,registers);

    //IR <- MDR
    registers_get_register(registers,&ir,REG_MDR);
    registers_set_register(registers,ir,REG_IR);

    ///DECODE
    Register opcode = ((_DATAMASK_OPCODE*)(&ir))->code;

    ///EVALUATE ADDRESS
    Register addr;
    switch(opcode) //switch on IR OPCODE
    {
        case OPCODE_ST:
            addr = pc + _controller_util_sext(((_DATAMASK_ST*)(&ir))->pcoffset9,9);
            break;
        case OPCODE_STR:
            registers_get_register(registers,&temp,((_DATAMASK_STR*)(&ir))->baser);
            addr = temp + _controller_util_sext(((_DATAMASK_STR*)(&ir))->pcoffset6,6);
            break;
        case OPCODE_LD:
            addr = pc + _controller_util_sext(((_DATAMASK_LD*)(&ir))->pcoffset9,9);
            break;
        case OPCODE_LDR:
            registers_get_register(registers,&temp,((_DATAMASK_LDR*)(&ir))->baser);
            addr = temp + _controller_util_sext(((_DATAMASK_LDR*)(&ir))->pcoffset6,6);
            break;
        case OPCODE_LEA:
            addr = pc + _controller_util_sext(((_DATAMASK_LEA*)(&ir))->pcoffset9,9);
            break;
        case OPCODE_BR:
            addr = pc + _controller_util_sext(((_DATAMASK_BR*)(&ir))->pcoffset7,7);
            break;
        case OPCODE_JMP:
            registers_get_register(registers,&addr,((_DATAMASK_JMP*)(&ir))->baser);
            break;
    }


    ///FETCH OPERANDS
    Register op1;
    Register op2;
    switch(opcode) //switch on IR OPCODE
    {
        case OPCODE_ADD:
        case OPCODE_AND:
        case OPCODE_SUB: //sext and add op2 if imm, simply load op2 if not
            if(((_DATAMASK_ADD_IMM5*)(&ir))->one)   op2 = _controller_util_sext(((_DATAMASK_ADD_IMM5*)(&ir))->imm5,5);
            else                                    registers_get_register(registers,&op2,((_DATAMASK_ADD_REGS*)(&ir))->sr2);
        case OPCODE_NOT: //load op1 for all above as well as this
            registers_get_register(registers,&op1,((_DATAMASK_ADD_REGS*)(&ir))->sr1);
            break;
        case OPCODE_ST:
        case OPCODE_STR:
            //I do not believe these have a FETCH phase
            break;
        case OPCODE_LD:
        case OPCODE_LDR:
            registers_set_register(registers,addr,REG_MAR);
            memory_get(memory,registers);
            registers_get_register(registers,&op1,REG_MDR);
            break;
        case OPCODE_LEA:
            //I do not believe this has a FETCH phase
            break;
        case OPCODE_BR:
            registers_get_register(registers,&op1,REG_PSR); //load the PSR to be later casted
            break;
        case OPCODE_JMP:
            //I do not believe this has a FETCH phase
            break;
    }

    ///EXECUTE
    switch(opcode) //switch on IR OPCODE
    {
        case OPCODE_ADD:
        case OPCODE_AND:
        case OPCODE_SUB:
        case OPCODE_NOT:
        case OPCODE_ST:
        case OPCODE_STR:
        case OPCODE_LD:
        case OPCODE_LDR:
        case OPCODE_LEA:
        case OPCODE_BR:
        case OPCODE_JMP:
            break;
    }

    ///STORE RESULT



    return 0;
}

Register _controller_util_sext(Register in, unsigned short bits)
{
    Register bitmask = 0;
    int i;
    for(i = 0; i < bits; i++)
        bitmask = bitmask | (1<<i);

    printf(" %x %x %x\n",in, bitmask, i);
    in = in & bitmask;
    printf(" %x %x %x\n",in, bitmask, i);
    bitmask = bitmask >> 1; //shift 1s right one;
    printf(" %x %x %x\n",in, bitmask, i);
    Register sign = in & ~bitmask;
    printf(" %x %x %x %x\n",in, bitmask, i, sign);

    for(; i <= 16; i++)
    {
        printf("*%x %x %x %x\n",in, bitmask, i, sign);
        sign = sign << 1;
        in = in | sign;
    }
    printf(" %x %x %x\n",in, bitmask, i);
    printf("**********\n");

    return in;
}


//controller test driver
int main()
{
    printf("%d\n",(short)_controller_util_sext(0b11,2));
    printf("%d\n",(short)_controller_util_sext(0b01,2));
    printf("%d\n",(short)_controller_util_sext(0b11,3));
    printf("%d\n",(short)_controller_util_sext(0b101,3));
}
