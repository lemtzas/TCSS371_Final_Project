#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lc-plus.h"

int _main_temp_testing()
{
    Memory memory;
    memory_initialize(&memory);
}



void _main_error(error)
{
    if(error)
    {
        printf("ERROR: %s", error);
        exit(-1);
    }
}

//manual test and simulation driver for alu.c (PROJECT 3)
int _main_lc_plus_loop()
{
    char* error = 0;
    Memory memory;
    Registers registers;
    CPU cpu;
    Debug debug;

    _main_error( memory_initialize(&memory) );
    _main_error( registers_initialize(&registers) );
    _main_error( cpu_initialize(&cpu) );
    _main_error( debug_initialize(&debug) );

    //the main loop
    int user_wants_to_continue = 0;
    _main_error( debug_monitor( &debug, &cpu , &registers , &memory) );
    _main_error( debug_do_step_ask( &debug, &cpu , &registers , &memory ,&user_wants_to_continue) );
    while(user_wants_to_continue) {
        _main_error( cpu_run_step(&cpu, &memory, &registers) );
        if(user_wants_to_continue != 2) _main_error( debug_monitor( &debug, &cpu , &registers , &memory) );
        _main_error( debug_do_step_ask( &debug, &cpu , &registers , &memory ,&user_wants_to_continue) );
    }
    return 0;
}

//int main()
//{
//    return _main_lc_plus_loop();
//}
