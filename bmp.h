#ifndef BMP
#define BMP
#include "image.h"
#include <stdio.h>
#include <stdint.h>

// Описание для gcc и clang
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

/*  deserializer   */
enum readStatus  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_PIXELS,
  READ_INVALID_HEADER,
  READ_MALLC_ERROR,
  READ_ERROR
  /* коды других ошибок  */
  };

enum readStatus fromBmp(FILE* in, struct image* img);

/*  serializer   */
enum  writeStatus  {
  WRITE_OK = 0,
  WRITE_ERROR,
  WRITE_SOURCE_NULL 
  /* коды других ошибок  */
};

enum writeStatus toBmp(FILE* out, struct image const* img);

#endif
