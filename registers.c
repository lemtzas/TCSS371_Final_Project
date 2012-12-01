#include "registers.h"

//initializes all registers
char* registers_initialize( Registers *registers )
{
    int i;
    for(i = 0; i < 8; i++)
        registers->r[i] = 0x0000;

    registers->ir = 0x0000;
    registers->pc = 0x0000;
    registers->mar = 0x0000;
    registers->mdr = 0x0000;
    registers->psr = 0x0000;
    return 0;
}


//char* error_string registers_get_register(  Registers *registers , Register *register_out , unsigned short REGISTER_ID )
char* registers_get_register( Registers *this , Register *register_out , unsigned short REGISTER_ID )
{
    if(!register_out) return "registers_get_register: register_out cannot be null";
    if(!this) return "registers_get_register: this cannot be null";
    Register *reg = _registers_id_to_register_ptr(this,REGISTER_ID);

    return 0;
}


//char* error_string registers_set_register(  Registers *registers , Register *register_out , unsigned short REGISTER_ID )
char* registers_set_register( Registers *this , Register register_in , unsigned short REGISTER_ID )
{
    return 0;
}

//internal function; returns a register reference depending on ID
Register* _registers_id_to_register_ptr(Registers *this, unsigned short REGISTER_ID)
{
    switch(REGISTER_ID)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return &(registers->r[REGISTER_ID])
            break;
        case REG_IR: //8
            return &(registers->ir);
            break;
        case REG_PC: //9
            return &(registers->pc);
            break;
        case REG_MAR: //10
            return &(registers->mar);
            break;
        case REG_MDR: //11
            return &(registers->mdr);
            break;
        case REG_PSR: //12
            return &(registers->psr);
            break;
        default: //OH GOD PANIC!
            exit(5);
    }
}
