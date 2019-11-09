#ifndef NITELITE_CORE_H
#define NITELITE_CORE_H

#include "stdlib.h"

typedef unsigned char byte;

inline int availableMemory() {
    int size = 2048; // Use 2048 with ATmega328
    byte *buf;

    while ((buf = (byte *) malloc(--size)) == nullptr);

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

char *int2str(int i);


//#define PIN_A0   (14)
//#define PIN_A1   (15)
//#define PIN_A2   (16)
//#define PIN_A3   (17)
//#define PIN_A4   (18)
//#define PIN_A5   (19)
//#define PIN_A6   (20)
//#define PIN_A7   (21)

#define OLED_PIN 2
#define R_OUT_PIN 3
#define G_OUT_PIN 5
#define B_OUT_PIN 6
#define R_IN_PIN 16
#define G_IN_PIN 15
#define B_IN_PIN 14
#define UP_PIN 4
#define DOWN_PIN 7

#define CONFIG_VERSION 2
#define TIMEOUT_DIVISOR 25
#define SCREEN_TIMEOUT_MULT 5
#define SCREEN_TIMEOUT_MAX 50
#define LIGHTS_TIMEOUT_MULT 20
#define LIGHTS_TIMEOUT_MAX 200

struct Config {
    byte version;
    byte screenTimeout;
    byte lightsTimeout;
    short rMin;
    short rMax;
    short gMin;
    short gMax;
    short bMin;
    short bMax;
};

#endif //NITELITE_CORE_H