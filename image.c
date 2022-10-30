#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "image.h"

static size_t indexOfCoordinates(struct image image, size_t x, size_t y) {
    return y * image.width + x;
}

void imageCreate(struct image* image, size_t width, size_t height) {
    image->width = width;
    image->height = height;
    image->data = malloc(width * height * sizeof(struct pixel)); 
}

void imageDestroy(struct image* const image) {
    if (image == NULL)
        return;
    free(image->data);
}

struct pixel imageGetPixel(const struct image image, size_t x, size_t y) {
    const size_t index = indexOfCoordinates(image, x, y);
    return image.data[index];
}

void imageSetPixel(struct image image, struct pixel pixel, size_t x, size_t y) {
    const size_t index = indexOfCoordinates(image, x, y);
    image.data[index] = pixel;
}

