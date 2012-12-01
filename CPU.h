#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "registers.h"

///CPU storage
typedef struct {

} CPU;

//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_initialize(CPU *this);


//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_run_step(CPU *this, Registers *registers, Memory *memory);

#endif
