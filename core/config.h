#ifndef NITELITE_CONFIG_H
#define NITELITE_CONFIG_H

#include "common.h"

#define CONFIG_VERSION 1
#define CONFIG_ADDRESS 100

struct Config {
    byte version;
    short rMin;
    short rMax;
    short gMin;
    short gMax;
    short bMin;
    short bMax;
};

#endif //NITELITE_CONFIG_H
