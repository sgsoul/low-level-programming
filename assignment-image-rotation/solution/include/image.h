#ifndef IMAGE
#define IMAGE

#include <inttypes.h>
#include <stddef.h>

struct pixel { 
  uint8_t b, g, r; 
};

struct image {
  uint64_t width, height;
  struct pixel* data;
};

struct image imageCreate(struct image* image, size_t width, size_t height);

void imageDestroy(struct image* image); //*img

struct pixel imageGetPixel(const struct image* image, size_t x, size_t y);

void imageSetPixel(struct image* image, struct pixel pixel, size_t x, size_t y);

#endif
