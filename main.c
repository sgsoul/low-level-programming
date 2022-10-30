#include <stdio.h>
#include "image.h"
#include "file.h"
#include "logger.h"
#include "bmp.h"
#include "rotate.h"


int main( int argc, char** argv ) {
//    (void) argc; (void) argv; // supress 'unused parameters' warning

    if (argc != 3) {
        printf("Invalid input arguments!");
        return 1;
    }
 
    struct image image;

    FILE* file = NULL;
    
    enum openStatus openStatus = openFile(file, argv[1], RB);
    if (openStatus != OPEN_OK) {
        printerr("err1\n");
        err("err2\n");
        return 0;
    }
    printf("с говно");
    fromBmp(file, &image);

    enum closeStatus saveStatus = closeFile(file);
    if (saveStatus != CLOSE_OK) {
        printerr("err3\n");
        err("err4\n");
        return 0;
    }

   //struct image rotated = rotate(image);

    imageDestroy(&image);
    //imageDestroy(&rotated);

    return 0;
}
