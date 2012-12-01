#include "controller.h"

char* controller_run_step(Controller *this, ALU *alu, Registers *registers, Memory *memory)
{
    Register temp;
    ///FETCH
    //MAR <- PC
    registers_get_register(registers,&temp,REG_PC);
    registers_set_register(registers,temp,REG_MAR);

    //PC <- PC + 1
    registers_set_registeR(registers,++temp,REG_PC);

    //LOAD MEMORY
    memory_get(memory,registers);

    //IR <- MDR
    registers_get_register(registers,&temp,REG_MDR);
    registers_set_register(registers,temp,REG_IR);

    ///DECODE
    switch

    ///EVALUATE ADDRESS


    ///FETCH OPERANDS


    ///EXECUTE


    ///STORE RESULT


}
