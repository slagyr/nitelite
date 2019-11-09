#include "Mode.h"
#include "Controller.h"

bool Mode::fade(float rStep, float gStep, float bStep, byte rLimit, byte gLimit, byte bLimit) {
    bool result = false;
    float value;

    value = stepColor(Controller::instance->red, rStep, rLimit);
    result = fadeLimitHit(result, value, rStep, rLimit);
    Controller::instance->red = value;

    value = stepColor(Controller::instance->green, gStep, gLimit);
    result = fadeLimitHit(result, value, gStep, gLimit);
    Controller::instance->green = value;

    value = stepColor(Controller::instance->blue, bStep, bLimit);
    result = fadeLimitHit(result, value, bStep, bLimit);
    Controller::instance->blue = value;

    return result;
}

float Mode::stepColor(float value, float step, short limit) const {
    value += step;
    if (step > 0 && value > limit)
        value = limit;
    else if (step < 0 && value < limit)
        value = limit;

    if (value > 255)
        value = 255;
    else if (value < 0)
        value = 0;

    return value;
}

bool Mode::fadeLimitHit(bool result, float color, float step, byte limit) const {
    if (result)
        return true;
    else if (step < 0 && color <= limit)
        result = true;
    else if (step > 0 && color >= limit)
        result = true;
    return result;
}

byte Mode::minb(byte a, byte b) {
    if (a < b)
        return a;
    else
        return b;
}

//byte Mode::maxb(byte a, byte b) {
//    if (a > b)
//        return a;
//    else
//        return b;
//}

float Mode::minf(float a, float b) {
    if(a < b)
        return a;
    else
        return b;
}

//float Mode::maxf(float a, float b) {
//    if(a > b)
//        return a;
//    else
//        return b;
//}

void Mode::randomColor(Color *c) {
    c->r = Controller::instance->hardware->randomLong(256);
    c->g = Controller::instance->hardware->randomLong(256);
    c->b = Controller::instance->hardware->randomLong(256);
}

void Mode::randomBrightColor(Color *c) {
    long choice = Controller::instance->hardware->randomLong(7);
    c->r = 0;
    c->g = 0;
    c->b = 0;
    switch (choice) {
        case 0:
            c->r = 255;
            break;
        case 1:
            c->g = 255;
            break;
        case 2:
            c->b = 255;
            break;
        case 3:
            c->r = 255;
            c->g = 255;
            break;
        case 4:
            c->g = 255;
            c->b = 255;
            break;
        case 5:
            c->r = 255;
            c->b = 255;
            break;
        case 6:
            c->r = 255;
            c->g = 255;
            c->b = 255;
            break;
    }
}

//
//byte Mode::min() {
//    byte min = Controller::instance->red;
//    if(Controller::instance->green < min)
//        min = Controller::instance->green;
//    if(Controller::instance->blue < min)
//        min = Controller::instance-> blue;
//    return min;
//}
//
//byte Mode::max() {
//    byte max = Controller::instance->red;
//    if(Controller::instance->green > max)
//        max = Controller::instance->green;
//    if(Controller::instance->blue > max)
//        max = Controller::instance-> blue;
//    return max;
//}
