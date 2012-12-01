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

#endif
