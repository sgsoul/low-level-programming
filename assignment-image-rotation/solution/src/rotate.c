#include "rotate.h"

struct image rotate(struct image const source) {
    struct image rotatedImage;
    imageCreate(&rotatedImage, source.height, source.width);

    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j++) {
            const struct pixel pixel = imageGetPixel(&source, j, i);
            imageSetPixel(&rotatedImage, pixel, rotatedImage.width - i - 1, j);
        }
    }
    return rotatedImage;
}
