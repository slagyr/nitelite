#ifndef NITELITE_DISPLAY_H
#define NITELITE_DISPLAY_H

#include "common.h"

class Display {

public:
    virtual void setup() = 0;

    virtual void splash() = 0;

    virtual void showHome() = 0;

};


#endif //NITELITE_DISPLAY_H
