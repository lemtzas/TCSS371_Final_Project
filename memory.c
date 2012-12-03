#include "memory.h"

char* memory_initialize( Memory *this )
{
    if(this == 0) return "memory_initialize: this must not be null";
    int i;
    for(i = 0; i < LCPLUS_MEMORY_SIZE; i++)
        this->location[i] = 0x0000;
    return 0;
}


//char* error_string memory_get( Memory *memory , Register *data_out , unsigned short address)
char* memory_get( Memory *this, Registers *registers)
{
    Register mar_tmp;
    Register mdr_tmp;
    registers_get_register(registers,&mar_tmp,REG_MAR);

    if(this == 0) return "memory_get: this must not be null";
    if(mar_tmp >= LCPLUS_MEMORY_SIZE || mar_tmp < 0 ) return "memory_get: mar out of range";

    mdr_tmp = this->location[mar_tmp];

    registers_set_register(registers,mdr_tmp,REG_MDR);

    return 0;
}


//char* error_string memory_set( Memory *memory , Register data_in , unsigned short address)
char* memory_set( Memory *this , Registers *registers)
{
    Register mar_tmp;
    Register mdr_tmp;
    registers_get_register(registers,&mdr_tmp,REG_MDR);
    registers_get_register(registers,&mar_tmp,REG_MAR);

    if(this == 0) return "memory_set: this must not be null";
    if(mar_tmp >= LCPLUS_MEMORY_SIZE || mar_tmp < 0 ) return "memory_set: mar out of range";

    this->location[mar_tmp] = mdr_tmp;

    return 0;
}
