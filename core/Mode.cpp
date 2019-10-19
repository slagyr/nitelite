#include "Mode.h"
#include "Controller.h"

bool Mode::fade(float rStep, float gStep, float bStep, byte rLimit, byte gLimit, byte bLimit) {
    bool result = false;
    float value;

    value = stepColor(controller->red, rStep, rLimit);
    result = fadeLimitHit(result, value, rStep, rLimit);
    controller->red = value;

    value = stepColor(controller->green, gStep, gLimit);
    result = fadeLimitHit(result, value, gStep, gLimit);
    controller->green = value;

    value = stepColor(controller->blue, bStep, bLimit);
    result = fadeLimitHit(result, value, bStep, bLimit);
    controller->blue = value;

    return result;
}

float Mode::stepColor(float value, float step, short limit) const {
    value += step;
    if(step > 0 && value > limit)
        value = limit;
    else if(step < 0 && value < limit)
        value = limit;

    if (value > 255)
        value = 255;
    else if (value < 0)
        value = 0;

    return value;
}

bool Mode::fadeLimitHit(bool result, float color, float step, byte limit) const {
    if(result)
        return true;
    else if (step < 0 && color <= limit)
        result = true;
    else if (step > 0 && color >= limit)
        result = true;
    return result;
}
//
//byte Mode::min() {
//    byte min = controller->red;
//    if(controller->green < min)
//        min = controller->green;
//    if(controller->blue < min)
//        min = controller-> blue;
//    return min;
//}
//
//byte Mode::max() {
//    byte max = controller->red;
//    if(controller->green > max)
//        max = controller->green;
//    if(controller->blue > max)
//        max = controller-> blue;
//    return max;
//}
