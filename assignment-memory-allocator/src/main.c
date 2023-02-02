#include "tests/test.h"
#include <stdio.h>
#include "mem_internals.h"
#include "mem.h"

int main() {
    if(!run_all()){
        fputs("tests failed", stderr);
        return -1;
    }
    fputs("all tests completed", stdout);
    return 0;
}
