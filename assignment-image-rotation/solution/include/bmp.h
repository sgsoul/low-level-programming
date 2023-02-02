#ifndef BMP
#define BMP
#include "image.h"
#include <stdio.h>
#include <stdint.h>

// Описание для gcc и clang


/*  deserializer   */
enum readStatus  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_PIXELS,
  READ_INVALID_HEADER,
  READ_MALLC_ERROR,
  READ_ERROR
  };

enum readStatus fromBmp(FILE* in, struct image* img);

/*  serializer   */
enum  writeStatus  {
  WRITE_OK = 0,
  WRITE_ERROR,
  WRITE_SOURCE_NULL
};

enum writeStatus toBmp(FILE* out, struct image const* img);

#endif
