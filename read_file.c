#include "read_file.h"
#include "debug_display.h"

char* readFile(Memory *memory) {
    FILE *fp;
    int i=0;
    char* string;
    Register* temp;
    char file[256];
    char retry;
    int res;
    do
    {
        retry = 0;
        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+1,_D_INPUT_SY);
        printf("\033[%d;%dHEnter a File Name (max 256 chars): ",_D_INPUT_SX+1,_D_INPUT_SY);
        printf("");
        res = scanf("%s", file);
        if(res == 0) {
            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
            printf("\033[%d;%dHInvalid Input",_D_INPUT_SX+2,_D_INPUT_SY);
            while (getchar() != '\n'); //remove offending characters
            retry = 1;
        }

        printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
        printf("\033[%d;%dHLoading the File",_D_INPUT_SX+2,_D_INPUT_SY);
        /* open the file */
        fp = fopen(file, "r");
        if(fp == NULL) {
            printf("\033[%d;%dH                                                                                ",_D_INPUT_SX+2,_D_INPUT_SY);
            printf("\033[%d;%dHFile not Found",_D_INPUT_SX+2,_D_INPUT_SY);
            retry = 1;
        }
    } while( retry );
    /* open the file */
    //fp = fopen(file, "r");
    if (fp == NULL) return "Could not open file.";

        printf("loading '%s'\n",file);
    //printf("loading %s %x\n",file,fp);
    while (fscanf(fp, "%04x", &temp) == 1 && i <= LCPLUS_MEMORY_SIZE){
        memory->location[i] = temp;
        i++;
    }
        printf("loading '%s'\n",file);
    //printf("loading %s\n\n",file);
    /* close the file */
    fclose(fp);

    return 0;
}


///Test driver for readFile
//int main()
//{
//    Memory memory;
//    memory_initialize(&memory);
//
//    readFile("read_file_test.txt",&memory);
//
//
//    int i = 0;
//    for(i = 0; i < 100; i++)
//    {
//        if( memory.location[i] )
//        {
//            printf("%04x\n",memory.location[i]);
//        }
//    }
//}
