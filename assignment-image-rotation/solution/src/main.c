#include "bmp.h"
#include "file.h"
#include "image.h"
#include "logger.h"
#include "rotate.h"
#include <stdio.h>


int main( int argc, char** argv ) {

    if (argc != 3) {
        fprintf(stderr, "Wrong count of arguments!");
        return 1;
    }
 
    struct image image;

    FILE* file = openFile(argv[1], FM_RB);
    if (file == NULL) {
        err("Open eroror.\n");
        return 0;
    }


    fromBmp(file, &image);

    closeFile(file);

    struct image rotated = rotate(image);

    FILE* newFile = openFile(argv[2], FM_WB);
    toBmp(newFile, &rotated);

    imageDestroy(&image);
    imageDestroy(&rotated);

    closeFile(newFile);

    return 0;
}
