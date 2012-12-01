#ifndef DEBUG_H
#define DEBUG_H

#include "memory.h"
#include "CPU.h"
#include "registers.h"

///Debug storage
typedef struct {
} Debug;


//char* error_string debug_monitor( CPU &cpu , Registers &registers , Memory &memory )
char* debug_monitor( Debug *this, CPU *cpu , Registers *registers , Memory *memory );


//char* error_string debug_do_step_ask( CPU &cpu , Registers &registers , Memory &memory , Boolean &result )
char* debug_do_step_ask( Debug *this, CPU *cpu , Registers *registers, Memory *memory, Boolean *result );


#endif
