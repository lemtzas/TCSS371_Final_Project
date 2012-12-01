#ifndef CPU_H
#define CPU_H

#include "controller.h"
#include "memory.h"
#include "registers.h"

///CPU storage
typedef struct {
    Controller controller;
    ALU alu;
} CPU;

//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_initialize(CPU *this);


//char* error_string cpu_run_step(CPU *cpu, Registers *registers, Memory *memory)
char* cpu_run_step(CPU *this, Registers *registers, Memory *memory);

#endif
