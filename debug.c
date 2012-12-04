#include "debug.h"
#include "debug_display.h"
#include "read_file.h"

char* debug_initialize( Debug *this )
{
    this->line = 0;
    this->start = 0;
    this->end = this->start + 0xF;
    return 0;
}
//Displays the current status of all registers
char* debug_monitor( Debug *this, CPU *cpu , Registers *registers , Memory *memory )
{

	_debug_monitor_helper(this,cpu,registers,memory);

    return 0;
}

//steps, and asks if the user wishes to see input or quit
char* debug_do_step_ask( Debug *this, CPU *cpu , Registers *registers, Memory *memory, int *result )
{
    int answer = 0;
    char* error;
    do {
        printf("1) Load, 2) Step, 3) Run, 4) Show Mem, 5) Clear Mem, 6) Exit\n");
        printf("\033[%d;%dH\n\n\n\n\n",_D_INPUT_SX,_D_INPUT_SY);
        printf("\033[%d;%dH::                                                                              ",_D_INPUT_SX,_D_INPUT_SY);
        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+3,_D_INPUT_SY);
        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+4,_D_INPUT_SY);
        printf("\033[%d;%dH:: ",_D_INPUT_SX,_D_INPUT_SY);
        int res = 0;
        unsigned char retry = 0;
        do
        {
            retry = 0;
            //printf("\033[%d;%dH\n\n\n\n\n",_D_INPUT_SX,_D_INPUT_SY);
            printf("\033[%d;%dH::                                                                              ",_D_INPUT_SX,_D_INPUT_SY);
//            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
//            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
//            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+3,_D_INPUT_SY);
//            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+4,_D_INPUT_SY);
            printf("\033[%d;%dH:: ",_D_INPUT_SX,_D_INPUT_SY);
            res = scanf("%d", &answer);
            if(res == 0) {
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
                printf("\033[%d;%dHInvalid input!",_D_INPUT_SX+1,_D_INPUT_SY);
                while (getchar() != '\n'); //remove offending characters
                retry = 1;
            } else if(answer < 0 || answer > 6) {
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
                printf("\033[%d;%dHOut of Bounds!",_D_INPUT_SX+1,_D_INPUT_SY);
                retry = 1;
            }
        } while( retry );


        (*result) = 0;
        switch(answer)
        {
            case 1:
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: LOAD",_D_INPUT_SX+1,_D_INPUT_SY);
                memory_initialize(memory);
                registers_initialize(registers);
                cpu_initialize(cpu);
                readFile(memory);
                _debug_monitor_helper_set_line(this,registers->pc);
                _debug_monitor_helper(this,cpu,registers,memory);
                break;
            case 2:
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: STEP",_D_INPUT_SX+1,_D_INPUT_SY);
                error = cpu_run_step(cpu, registers, memory);
                _debug_monitor_helper_set_line(this,registers->pc);
                _debug_monitor_helper(this,cpu,registers,memory);
                break;
            case 3:
                do{
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: RUN",_D_INPUT_SX+1,_D_INPUT_SY);
                    error = cpu_run_step(cpu, registers, memory);
                    _debug_monitor_helper_set_line(this,registers->pc);
                    _debug_monitor_helper(this,cpu,registers,memory);
                } while(!cpu->controller.halt && registers->pc <= LCPLUS_MEMORY_SIZE);
                break;
            case 4:
            {
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: GOTO",_D_INPUT_SX,_D_INPUT_SY);
                int location;
                do
                {
                    retry = 0;
                    printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
                    printf("\033[%d;%dHWhere? 0x",_D_INPUT_SX+1,_D_INPUT_SY);
                    res = scanf("%x", &location);
                    if(res == 0) {
                        //printf("\t\tInvalid input!\n");
                        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
                        printf("\033[%d;%dHInvalid Input ",_D_INPUT_SX+2,_D_INPUT_SY);
                        while (getchar() != '\n'); //remove offending characters
                        retry = 1;
                    } else if(location < 0 || location > LCPLUS_MEMORY_SIZE) {
                        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
                        printf("\033[%d;%dHOut of Bounds ",_D_INPUT_SX+2,_D_INPUT_SY);
                        retry = 1;
                    }
                } while( retry );
                _debug_monitor_helper_set_line(this,location);
                _debug_monitor_helper(this,cpu,registers,memory);
            }
                break;
            case 5:
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: CLEARMEM",_D_INPUT_SX+1,_D_INPUT_SY);
                memory_initialize(memory);
                _debug_monitor_helper(this,cpu,registers,memory);
                break;
            case 6:
                printf("\033[%d;%dH                                                                                ",_D_INPUT_SX,_D_INPUT_SY);
                printf("\033[%d;%dH:: QUIT",_D_INPUT_SX+1,_D_INPUT_SY);
                (*result) = 0;
                _debug_monitor_helper(this,cpu,registers,memory);
                break;
            default:
                printf("wat");
        }
    } while(answer != 6);
    return error;
}
