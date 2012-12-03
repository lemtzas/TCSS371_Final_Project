#include "debug_display.h"
#include <stdio.h>

char* _debug_monitor_helper_set_line(Debug *this, unsigned short line)
{
    this->line = line;
    //calculate what to look at
    if(this->line > this->end || this->line < this->start)
    {
        if(this->line > this->end && (this->line - this->end) == 1)
        {
            this->end++;
            this->start++;
        } else if(this->line < this->start && (this->start - this->line) == 1)
        {
            this->end--;
            this->start--;
        } else {
            int temp = this->line - 0x8;
            if(temp < 0) temp = 0;
            this->start = temp;
            this->end = this->start + 0xF;
        }
    }
    return 0;
}
char* _debug_monitor_helper( Debug *this, CPU *cpu , Registers *registers , Memory *memory )
{
    printf("\033[%d;%dHRegisters",_D_REG_SX,_D_REG_SY);
    int i;
    for(i = 0; i < 8; i++)
    {
        printf("\033[%d;%dHR%d   0x%04X",_D_REG_SX+i+1,_D_REG_SY,i,registers->r[i]);
    }

    printf("\033[%d;%dHSpecial Registers",_D_REG_SP_SX,_D_REG_SP_SY);
    printf("\033[%d;%dHPC:  0x%04X    IR:  0x%04X",_D_REG_SP_SX+1,_D_REG_SY,registers->pc,registers->ir);
    printf("\033[%d;%dHMAR: 0x%04X    MDR: 0x%04X",_D_REG_SP_SX+2,_D_REG_SY,registers->mar,registers->mdr);
    printf("\033[%d;%dHStatus Flags",_D_REG_SP_SX+3,_D_REG_SY);

	PSR psr;
	registers_get_register(registers,&psr,REG_PSR);
	Bit n;
	Bit z;
	Bit c;
	Bit o;
	Bit p;
	PSR_get_nzco(&psr,&n,&z,&c,&o);
	p = not(or(n,z));
    printf("\033[%d;%dHN: %d, Z: %d, P: %d, C: %d, O: %d",_D_REG_SP_SX+4,_D_REG_SY,n,z,p,c,o);

    printf("\033[%d;%dH Memory",_D_MEM_SX,_D_MEM_SY);
    for(i = 0; i <= this->end - this->start; i++)
    {
        if(this->start + i == this->line)
            printf("\033[%d;%dH>0x%04X: 0x%04X",_D_MEM_SX+2+i,_D_MEM_SY,this->start+i,memory->location[this->start+i]);
        else
            printf("\033[%d;%dH 0x%04X: 0x%04X",_D_MEM_SX+2+i,_D_MEM_SY,this->start+i,memory->location[this->start+i]);
    }

    //end in a reasonable place
    printf("\033[%d;%dH:",_D_FINAL_SX,_D_FINAL_SY);
}

///Debug Monitor Helper test driver
//int main()
//{
//    Debug debug;
//    CPU cpu;
//    Registers registers;
//    Memory memory;
//
//    debug_initialize(&debug);
//    cpu_initialize(&cpu);
//    registers_initialize(&registers);
//    memory_initialize(&memory);
//
//    _debug_monitor_helper_set_line(&debug, 0x0080);
//    _debug_monitor_helper(&debug,&cpu,&registers,&memory);
//}
