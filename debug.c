#include "debug.h"

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

	Register register_ptr;
	Register register_ptr2;
	// get the 8 general purpose registers
	int i;
//	printf("\n"); //printf("General Purpose Registers:\n");
	for(i=0;i<4;i++) {
		registers_get_register(registers,&register_ptr,i);
		registers_get_register(registers,&register_ptr2,i+4);
		printf("R%d: %04x\tR%d: %04x\n",i,register_ptr,i+4,register_ptr2);
	}
	printf("\n");

	//IR
	registers_get_register(registers,&register_ptr,REG_IR);
	printf("IR: %04x\t",register_ptr);   ///this needs a value to print

	//PC
	registers_get_register(registers,&register_ptr,REG_PC);
	printf("PC: %04x\n",register_ptr);   ///this needs a value to print

	//MAR
	registers_get_register(registers,&register_ptr,REG_MAR);
	printf("MAR: %04x\t",register_ptr);   ///this needs a value to print

	//MDR
	registers_get_register(registers,&register_ptr,REG_MDR);
	printf("MDR: %04x\n",register_ptr);   ///this needs a value to print

	//PSR
	PSR psr;
	registers_get_register(registers,&psr,REG_PSR);
	Bit n;
	Bit z;
	Bit c;
	Bit o;
	Bit p;
	PSR_get_nzco(&psr,&n,&z,&c,&o);
	p = not(or(n,z));
	printf("PSR: n:%d z:%d p:%d c:%d o:%d\n",n,z,p,c,o);

    return 0;
}

//steps, and asks if the user wishes to see input or quit
char* debug_do_step_ask( Debug *this, CPU *cpu , Registers *registers, Memory *memory, int *result )
{
	char* error;
	error = cpu_run_step(cpu, registers, memory);
	printf("1: Step and view debug\n2: Step without viewing debug\n0: Quit\n");

	int res = 0;
	unsigned char retry = 0;
    do
    {
        retry = 0;
        printf("Which? ");
        res = scanf("%d", result);
        if(res == 0) {
            //printf("\t\tInvalid input!\n");
            while (getchar() != '\n'); //remove offending characters
            retry = 1;
        } else if(*result < 0 || *result > 2) {
            //printf("\t\tOut of bounds!\n");
            retry = 1;
        }
    } while( retry );
    return error;
}
