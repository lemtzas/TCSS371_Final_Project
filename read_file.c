#include "read_file.h"

char* readFile(char* file,Memory *memory) {
    //printf("loading %s\n",file);
    FILE *fp;
    int i=0;
    char* string;
    Register* temp;
    /* open the file */
    fp = fopen(file, "r");
    if (fp == NULL) return "Could not open file.";

    //printf("loading %s %x\n",file,fp);
    while (fscanf(fp, "%04x", &temp) == 1){
        memory->location[i] = temp;
        i++;
    }
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
