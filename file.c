#include <stdio.h>
#include "file.h"

static const char *fileMode[] = {
        [RB] = "rb",
        [WB] = "wb",
        [AB] = "ab",
};

enum openStatus openFile(FILE *file, const char *fileName, enum fileMode mode) {
    file = fopen(fileName, fileMode[mode]);
    if (file == NULL) return OPEN_ERROR;
    return OPEN_OK;
}

enum closeStatus closeFile(FILE *file) {
    fclose(file);
    return CLOSE_OK;
}
