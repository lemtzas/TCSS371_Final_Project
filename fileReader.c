   #include <stdio.h>
   #include <stdlib.h>
   
   char* readFile(char* file){
    FILE *fp;
    int i=0;
	char string[1100];
	char temp[];
    /* open the file */
    fp = fopen(file, "r");
    if (fp == NULL) {
         printf("Could not open file.\n");
         exit(0);
    }
   
    while (fscanf(fp, "%d,%d\n", &string[]) == 1){
		i++;
	}
    /* close the file */
    fclose(fp);
   
    return string;
   }