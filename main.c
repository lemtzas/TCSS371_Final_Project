#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "alu.h"

//manual test and simulation driver for alu.c
int main()
{
    int reg_init_count = 0;
    int i;
    int res = 0;
    bool retry = false;
    Register r[8];


    ///opening
    printf("ALU Simulator, by David Sharer.\n\n");

    ///get input count
    res = 0;
    do
    {
        retry = false;
        printf("Input number of registers to initialize (1 up to 8): ");
        res = scanf("%d", &reg_init_count);
        if(res == 0) {
            printf("\t\tInvalid input!\n");
            while (getchar() != '\n'); //remove offending characters
            retry = true;
        } else if(reg_init_count < 1 || reg_init_count > 8) {
            printf("\t\tOut of bounds!\n");
            retry = true;
        }
    } while( retry );


    ///get register values
    printf("\nInput values as 16 bit hexadecimal numbers, e.g. FA35 (no leading 0x)\n");
    printf("\nRegisters will be loaded in order from R0 to R%d\n\n",reg_init_count-1);
    res = 0;
    unsigned short temp;
    for(i = 0; i < reg_init_count; i++) {
        do {
            retry = false;
            printf("Input register %d: ",i);
            res = scanf("%x",&(temp));
            r[i] = temp;
            if(res == 0) {
                printf("\t\tInvalid input!\n");
                while (getchar() != '\n'); //remove offending characters
                retry = true;
            }
        } while( retry );
    }

    ///get operation
    printf("\n\nOperations - 1) ADD, 2) SUB, 3) NEG, 4) NOT, 5) AND, 6) OR\n");
    res = 0;
    int operation = -1;
    do
    {
        retry = false;
        printf("Input operation: ");
        res = scanf("%d", &operation);
        if(res == 0) {
            printf("\t\tInvalid input!\n");
            while (getchar() != '\n'); //remove offending characters
            retry = true;
        } else if(operation < 1 || operation > 6) {
            printf("\t\tOut of bounds!\n");
            retry = true;
        }
    } while( retry );


    ///specify registers

    //source1
    printf("\nSpecify registers to operate on\n");
    res = 0;
    int source1 = -1;
    do
    {
        retry = false;
        printf("Source1: ");
        res = scanf("%d", &source1);
        if(res == 0) {
            printf("\t\tInvalid input!\n");
            while (getchar() != '\n'); //remove offending characters
            retry = true;
        } else if(source1 < 0 || source1 > 7) {
            printf("\t\tOut of bounds!\n");
            retry = true;
        }
    } while( retry );

    //source2
    res = 0;
    int source2 = -1;
    if( !(operation == 3 || operation == 4) ) //if not NEG or NOT (unary operators)
    {
        do
        {
            retry = false;
            printf("Source2: ");
            res = scanf("%d", &source2);
            if(res == 0) {
                printf("\t\tInvalid input!\n");
                while (getchar() != '\n'); //remove offending characters
                retry = true;
            } else if(source2 < 0 || source2 > 7) {
                printf("\t\tOut of bounds!\n");
                retry = true;
            }
        } while( retry );
    }

    //destination
    res = 0;
    int destination = -1;
    do
    {
        retry = false;
        printf("Destination: ");
        res = scanf("%d", &destination);
        if(res == 0) {
            printf("\t\tInvalid input!\n");
            while (getchar() != '\n'); //remove offending characters
            retry = true;
        } else if(destination < 0 || destination > 7) {
            printf("\t\tOut of bounds!\n");
            retry = true;
        }
    } while( retry );

    //operation output
    printf("\nRegister%d ",source1);
    switch(operation) {
        case 1:
            printf("ADD");
            break;
        case 2:
            printf("SUB");
            break;
        case 3:
            printf("NEG");
            break;
        case 4:
            printf("NOT");
            break;
        case 5:
            printf("AND");
            break;
        case 6:
            printf("OR");
            break;
        default:
            printf("   !PANIC!   ");
    }
    if(source2 != -1) printf(" Register%d",source2);
    printf(" --> Register%d\n\n",destination);



    //perform designated operation
    ALU alu;
    PSR psr;
    ALU_set_src1(&alu,r[source1]);
    if(source2 != -1) ALU_set_src2(&alu,r[source2]);
    switch(operation) {
        case 1:
            ALU_operation_add(&alu,&psr);
            break;
        case 2:
            ALU_operation_sub(&alu,&psr);
            break;
        case 3:
            ALU_operation_neg(&alu,&psr);
            break;
        case 4:
            ALU_operation_not(&alu,&psr);
            break;
        case 5:
            ALU_operation_and(&alu,&psr);
            break;
        case 6:
            ALU_operation_or(&alu,&psr);
            break;
        default:
            printf("\tInvalid Operation!   !PANIC!\n");
    }
    Register alu_result;
    ALU_get_result(&alu,&alu_result);

    r[destination] = alu_result; //store result

    //result
    printf("Result: %04x\n\n",alu_result);
    Bit n,z,c,o;
    PSR_get_nzco(&psr,&n,&z,&c,&o);
    printf("Condition codes: N = %d, Z = %d, C = %d, O = %d",n,z,c,o);
    return 0;
}
