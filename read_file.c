#include "read_file.h"

char* readFile(char* file,Memory *memory) {
    FILE *fp;
    int i=0;
    char* string;
    char* temp;
    /* open the file */
    fp = fopen(file, "r");
    if (fp == NULL) {
         printf("Could not open file.\n");
         exit(0);
    }

    while (fscanf(fp, "%x", &temp) == 1){
        strcat(string, temp);
        i++;
    }
    /* close the file */
    fclose(fp);

    return string;
}


///Test driver for readFile
int main()
{
    Memory memory;
    memory_initialize(&memory);

    readFile("read_file_test.txt",&memory);


    int i = 0;
    for()
}
