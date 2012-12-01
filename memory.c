#include "memory.h"

char* memory_initialize( Memory *this )
{
    if(this == 0) return "memory_initialize: this must not be null";
    int i;
    for(i = 0; i < LCPLUS_MEMORY_SIZE; i++)
        this->location[i] = 0x0000;
    return 0;
}


//char* error_string memory_get_location( Memory *memory , Register *data_out , unsigned short address)
char* memory_get_location( Memory *this, Register *data_out , unsigned short address)
{
    if(this == 0) return "memory_get_location: this must not be null";
    if(address >= LCPLUS_MEMORY_SIZE || address < 0 ) return "memory_get_location: address out of range";
    if(data_out == 0) return "memory_get_locoation: data out must not be null";
    (*data_out) = this->location[address];

    return 0;
}


//char* error_string memory_set_location( Memory *memory , Register data_in , unsigned short address)
char* memory_set_location( Memory *this , Register data_in , unsigned short address)
{
    if(this == 0) return "memory_set_location: this must not be null";
    if(address >= LCPLUS_MEMORY_SIZE || address < 0 ) return "memory_set_location: address out of range";
    this->location[address] = data_in;

    return 0;
}
