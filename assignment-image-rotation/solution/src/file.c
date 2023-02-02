#include "file.h"
#include <stdio.h>

static const char* const fileMode[] = {
        [FM_RB] = "rb",
        [FM_WB] = "wb",
        [FM_AB] = "ab",
};

FILE* openFile(const char *fileName, enum fileMode mode) {
    return fopen(fileName, fileMode[mode]);
}

void closeFile(FILE *file) {
    fclose(file);
}
