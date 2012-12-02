#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#include "debug.h"
#include "cpu.h"
#include "registers.h"
#include "memory.h"

char* _debug_monitor_helper( Debug *this, CPU *cpu , Registers *registers , Memory *memory );

#endif
