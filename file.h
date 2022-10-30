#ifndef FILE_H
#define FILE_H 
#include <stdio.h>

enum openStatus {
  OPEN_OK = 0,
  OPEN_ERROR
};

enum closeStatus {
  CLOSE_OK = 0,
  CLOSE_ERROR
};

enum fileMode {
  RB,
  WB,
  AB
};

enum openStatus openFile(FILE *file, const char *fileName, enum fileMode mode);

enum closeStatus closeFile(FILE *file);

#endif
