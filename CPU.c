#include "CPU.h"

//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_initialize(CPU *this)
{
    controller_initialize(&(this->controller));
    return 0;
}


//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_run_step(CPU *this, Registers *registers, Memory *memory)
{
    ///TODO: Is this correct?
    controller_run_step(&this->controller, &this->alu, registers, memory);
    return 0;
}
