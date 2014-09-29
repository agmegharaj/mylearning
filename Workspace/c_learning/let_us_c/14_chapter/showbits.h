#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "showbits.h"

#define BITS_IN_BYTE 8
#define INTEGRAL_TYPE unsigned int

void showbits(INTEGRAL_TYPE x) {
    int i;
    static int intSizeInBits = sizeof(INTEGRAL_TYPE) * BITS_IN_BYTE;
    static char symbol[2] = {'0','1'};
    char * binary = (char*) malloc(intSizeInBits + 1);

    memset(binary, 0, intSizeInBits + 1);

    for (i=0; i< intSizeInBits; i++) {
        binary[intSizeInBits-i-1] = symbol[(x>>i) & 0x01];
    }

    printf("%s\n", binary);
    free(binary);
}

