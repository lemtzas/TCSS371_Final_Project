#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#define _D_REG_SX 2
#define _D_REG_SY 0
#define _D_REG_SP_SX 13
#define _D_REG_SP_SY 0
#define _D_MEM_SX 0
#define _D_MEM_SY 40
#define _D_FINAL_SX 19
#define _D_FINAL_SY 0
#define _D_INPUT_SX 20
#define _D_INPUT_SY 0

#include "debug.h"
#include "cpu.h"
#include "registers.h"
#include "memory.h"

char* _debug_monitor_helper_set_line(Debug *this, unsigned short line);
char* _debug_monitor_helper( Debug *this, CPU *cpu , Registers *registers , Memory *memory );

#endif
