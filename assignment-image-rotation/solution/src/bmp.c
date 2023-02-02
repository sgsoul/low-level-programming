#include "bmp.h"
#include <malloc.h>
#include <stdio.h>

struct __attribute__((packed)) bmpHeader {
  uint16_t bfType;
  uint32_t bfileSize;
  uint32_t bfReserved;
  uint32_t bOffBits;
  uint32_t biSize;
  uint32_t biWidth;
  uint32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  uint32_t biXPelsPerMeter;
  uint32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
};

static uint32_t getPadding(uint64_t width) {
    if ((width * 3) % 4 == 0)
        return 0;
    return 4 - (width * 3 % 4);
}

static struct bmpHeader create_header(const struct image* img) {

    struct bmpHeader header = {0};
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
    return header;
}

enum writeStatus toBmp(FILE* out, struct image const* img) {
    struct bmpHeader header = create_header(img);

    fwrite(&header, sizeof(header), 1, out);
    if (fseek(out, header.bOffBits, SEEK_SET)) {
        return WRITE_ERROR;
    }
    const int64_t padding = getPadding(img->width);
    const uint32_t paddingObject[3] = {0, 0, 0};
    for (size_t i = 0; i < img->height; i++) {

        for(size_t j = 0; j < img->width; j++) {
            fwrite(&img->data[i * img->width + j], sizeof(struct pixel), 1, out);
        }
        fwrite(paddingObject, 1, padding, out);


    }

    return WRITE_OK;
}

enum readStatus fromBmp(FILE *in, struct image *img) {
    struct bmpHeader header;

    fread(&header, sizeof(struct bmpHeader), 1, in);

    if (header.bfType != 0x4D42)
    {
        return READ_INVALID_SIGNATURE;
    }

    if (fseek(in, header.bOffBits, SEEK_SET)) {
        return READ_ERROR;
    }

    struct image new_image = {0};
    imageCreate(&new_image, header.biWidth, header.biHeight);

    uint32_t padding = getPadding(new_image.width);

    for (size_t i = 0; i < new_image.height; i++)
    {
        if (fread(new_image.data + i * new_image.width, sizeof(struct pixel), new_image.width, in) != new_image.width) {
            return READ_INVALID_PIXELS;
        }
        if (fseek(in, padding, SEEK_CUR)){
            return READ_ERROR;
        }

    }

    *img = new_image;

    return READ_OK;
}
