#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

///Reads a file into Memory starting at 0x0000
//file: filename
//memory: existing Memory object to read the data into
//returns error string, if any; zero otherwise
char* readFile(char* file,Memory* memory);

#endif
