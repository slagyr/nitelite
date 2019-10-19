#ifndef NITELITE_MODE_H
#define NITELITE_MODE_H

#include "common.h"

class Controller;

class Mode {
public:
    virtual ~Mode() = default;

    virtual const char *getName() = 0;

    virtual void enter() = 0;

    virtual void tick() = 0;

    bool fade(float rStep, float gStep, float bStep, byte rLimit, byte gLimit, byte bLimit);
//    byte min();
//    byte max();
    byte minb(byte a, byte b);

protected:
    explicit Mode(Controller *controller) {
        this->controller = controller;
    };

    Controller *controller;

    bool fadeLimitHit(bool result, float color, float step, byte limit) const;

    float stepColor(float value, float step, short limit) const;
};

#endif //NITELITE_MODE_H
