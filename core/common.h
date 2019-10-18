#ifndef NITELITE_COMMON_H
#define NITELITE_COMMON_H

#include "stdlib.h"

typedef unsigned char byte;

inline int availableMemory() {
    int size = 2048; // Use 2048 with ATmega328
    byte *buf;

    while ((buf = (byte *) malloc(--size)) == NULL)
        ;

    free(buf);

    return size;
}

#ifndef PROGMEM
//#warning "PROGMEM undefined"
//#define PROGMEM
//#include <avr/pgmspace.h>
#define __ATTR_PROGMEM__ __attribute__((__progmem__))
#define PROGMEM __ATTR_PROGMEM__
#endif

#endif
