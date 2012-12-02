#include "debug.h"
<<<<<<< HEAD

char* debug_initialize( Debug *this )
{
    return 0;
}

=======
#include "register.h"
#include "registers.h"
#include "psr.h"
//Displays the current status of all registers
>>>>>>> Debug view
char* debug_monitor( Debug *this, CPU *cpu , Registers *registers , Memory *memory )
{

	//IR
	registers->registers_get(registers,register_ptr,REG_IR);
	register_ptr->register_get(register_ptr,value_ptr);
	printf("IR: %04x\t"); 
	
	//PC
	registers->registers_get(registers,register_ptr,REG_PC);
	register_ptr->register_get(register_ptr,value_ptr);
	printf("PC: %04x\n");
	// get the 8 general purpose registers
	int i;
	Register * register_ptr;
	unsigned short value;
	unsigned short * value_ptr = &value;
	printf("General Purpose Registers:\n");
	for(i=0;i<8;i++) {
		registers->registers_get(registers,register_ptr,i);
		register_ptr->register_get(register_ptr,value_ptr);
		printf("R%d: %04x\n",i,value);
	}
	
	//MAR
	registers->registers_get(registers,register_ptr,REG_MAR);
	register_ptr->register_get(register_ptr,value_ptr);
	printf("MAR: %04x\t"); 
	
	//MDR
	registers->registers_get(registers,register_ptr,REG_MDR);
	register_ptr->register_get(register_ptr,value_ptr);
	printf("MDR: %04x\n");
	
	//PSR
	registers->registers_get(registers,register_ptr,REG_PSR);
	Bit n;
	Bit z;
	Bit c;
	Bit o;
	register_ptr->PSR_get_nzco(register_ptr,&n,&z,&c,&o);
	printf("PSR: n:%d z:%d :c:%d o:%d\n",n,z,c,o);
	//what about p?
		
    return 0;
}

//steps, and asks if the user wishes to see input or quit
char* debug_do_step_ask( Debug *this, CPU *cpu , Registers *registers, Memory *memory, unsigned char *result )
{
	char* error;
	error = cpu->cpu_run_step(cpu, registers, memory);
	printf("1: Step and view debug\n2: Step without viewing debug\nQuit:0");
	scanf("%d",result);
    return error;
}
