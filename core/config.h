#ifndef NITELITE_CONFIG_H
#define NITELITE_CONFIG_H

#include "common.h"

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

#endif //NITELITE_CONFIG_H
