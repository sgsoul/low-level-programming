#include "logger.h"
#include <stdio.h>

void err(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}
