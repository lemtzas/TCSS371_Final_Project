#ifndef MEMORY_H
#define MEMORY_H

#include "register.h"
#include "registers.h"

#define LCPLUS_MEMORY_SIZE  0x1000


typedef struct {
    Register location[LCPLUS_MEMORY_SIZE];
} Memory;

char* memory_initialize( Memory *this );


//char* error_string memory_get_location( Memory *memory , Register *data_out , unsigned short address)
char* memory_get_location( Memory *this, Register *data_out , unsigned short address);


//char* error_string memory_set_location( Memory *memory , Register data_in , unsigned short address)
char* memory_set_location( Memory *this , Register data_in , unsigned short address);

#endif
