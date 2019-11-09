#ifndef NITELITE_MODE_H
#define NITELITE_MODE_H

#include "core.h"
#include "Screen.h"

#define SOFT_LOW_LIMIT 15

struct Color {
    byte r;
    byte g;
    byte b;
};

class Mode {
public:
    virtual ~Mode() = default;

    virtual const char *getName() = 0;

    virtual void enter() = 0;

    virtual void tick() = 0;

    bool fade(float rStep, float gStep, float bStep, byte rLimit, byte gLimit, byte bLimit);

    void randomColor(Color *c);
    void randomBrightColor(Color *c);


//    byte min();
//    byte max();
    byte minb(byte a, byte b);
//    byte maxb(byte a, byte b);
    float minf(float a, float b);
//    float maxf(float a, float b);

protected:

    bool fadeLimitHit(bool result, float color, float step, byte limit) const;

    float stepColor(float value, float step, short limit) const;
};

#endif //NITELITE_MODE_H
