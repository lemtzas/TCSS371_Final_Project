#ifndef DEBUG_H
#define DEBUG_H

#include "memory.h"
#include "CPU.h"
#include "bit_def.h"
#include "register.h"
#include "registers.h"
#include "psr.h"
//#include "debug_display.h"

#define STOPDEBUG 0
#define VIEWDEBUG 1
#define CONTINUE 2


///Debug storage
typedef struct {
    unsigned short line;
    unsigned short start;
    unsigned short end;
} Debug;

//initializes the debug structure
char* debug_initialize( Debug *this );

//char* error_string debug_monitor( CPU &cpu , Registers &registers , Memory &memory )
char* debug_monitor( Debug *this, CPU *cpu , Registers *registers , Memory *memory );


//char* error_string debug_do_step_ask( CPU &cpu , Registers &registers , Memory &memory , Boolean &result )
char* debug_do_step_ask( Debug *this, CPU *cpu , Registers *registers, Memory *memory, int *result );


#endif
