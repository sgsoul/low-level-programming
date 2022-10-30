#include "bmp.h"
#include <malloc.h>

uint32_t getPadding(uint64_t width) {
    if ((width * 3) % 4 == 0)
        return 0;
    return 4 - (width * 3 % 4);
}

enum writeStatus toBmp(FILE* out, struct image const* img) {
    //size_t padding = getPadding(img->width);
    struct bmpHeader header;
    header.bfType = 0x4D42;
    header.bOffBits = sizeof(struct bmpHeader);
    header.bfReserved = 0;
    header.bfileSize = (img->height) * (img->width) * sizeof(struct pixel) + (img->width) % 4 + sizeof(struct bmpHeader);
    header.biBitCount = 3 * 8;
    header.biClrImportant = 0;
    header.biClrUsed = 0;
    header.biCompression = 0;
    header.biHeight = img->height;
    header.biWidth = img->width;
    header.biPlanes = 1;
    header.biSize = 40;
    header.biSizeImage = (img->height) * ((img->width) * sizeof(struct pixel) + (img->width) % 4);
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    //fseek(out, 0, SEEK_SET)
    // write header
    fwrite(&header, sizeof(header), 1, out);
    // set pointer to data and write
    fseek(out, header.bOffBits, SEEK_SET);
    for (size_t i = 0; i < img->height; i++) {

        for(size_t j = 0; j < img->width; j++) {
            fwrite(&img->data[i * img->width + j], sizeof(struct pixel), 1, out);
        }
        //PADDING
        if (img->width % 4 != 0) {
            uint64_t padding = (4 - (img->width * sizeof(struct pixel)) % 4);
            for(uint64_t j = 0; j < padding; j++) {
                fputc(0, out);
            }
        }

    }

    return WRITE_OK;
}

enum readStatus fromBmp(FILE *in, struct image *img) {
    struct bmpHeader header;
    if (fread(&header, sizeof(header), 1, in) != 1)
    { 
        return READ_INVALID_HEADER;
    }
    if (header.biBitCount != 24 || !in)
    {
        return READ_INVALID_BITS;
    }
    if (header.bfType != 0x4D42)
    {
        return READ_INVALID_SIGNATURE;
    }
    printf("%zu", img->width);
    imageCreate(img, header.biWidth, header.biHeight);
    for (size_t i = 0; i < img->height; i++)
    {
        if (fread(img->data + i * img->width, sizeof(struct pixel), img->width, in) != img->width) {
            return READ_INVALID_PIXELS;
        }
        if (fseek(in, header.bOffBits, SEEK_CUR)){ //padding
            return READ_ERROR;
        }
    }
    return READ_OK;
}
