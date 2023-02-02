#ifndef FILE_H
#define FILE_H 
#include <stdio.h>


enum fileMode {
  FM_RB,
  FM_WB,
  FM_AB
};

FILE* openFile(const char *fileName, enum fileMode mode);

void closeFile(FILE *file);

#endif
