#include <Controller.h>
#include "YourDiscoMode.h"

#define DISCO_STEP_PERCENT -0.3
#define DISCO_WHOLE 32
#define DISCO_HALF 16
#define DISCO_QUARTER 8
#define DISCO_EIGTH 4
#define DISCO_SIXTEENTH 2
#define DISCO_BEATS 7

YourDiscoMode::YourDiscoMode() : Mode() {
    color = new Color();
}

const char *YourDiscoMode::getName() {
    return "Your Color Disco";
}

void YourDiscoMode::enter() {
    beatCount = 0;
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    chooseColor();
    chooseBeats();
}

void YourDiscoMode::chooseBeats() {
    repeat = false;
    beat1 = Controller::instance->hardware->randomLong(DISCO_BEATS);
    beat2 = Controller::instance->hardware->randomLong(DISCO_BEATS);
    while (beat2 == beat1)
        beat2 = Controller::instance->hardware->randomLong(DISCO_BEATS);
}

void YourDiscoMode::tick() {
    if (beatCount >= DISCO_WHOLE) {
        chooseColor();
        beatCount = 0;
        if (beat == beat1)
            beat = beat2;
        else {
            if (repeat) {
                chooseBeats();
                beat = beat1;
                repeat = false;
            } else {
                beat = beat1;
                repeat = true;
            }
        }
    }

    switch (beat) {
        case 0:
            quarters();
            break;
        case 1:
            eigths();
            break;
        case 2:
            stayingAlive();
            break;
        case 3:
            dancingQueen();
            break;
        case 4:
            youAreTheDancingQueen();
            break;
            break;
        case 5:
            anotherOneBytesTheDust();
            break;
        case 6:
            YMCA();
            break;
    }

    Controller::instance->writeRGB();
    beatCount++;
}

void YourDiscoMode::chooseColor() {
    Controller::instance->readRGB();
    color->r = Controller::instance->redInput;
    color->g = Controller::instance->greenInput;
    color->b = Controller::instance->blueInput;
}

void YourDiscoMode::writeColor() {
    Controller::instance->writeRGB(color->r, color->g, color->b);
}

void YourDiscoMode::pass() {
    float rStep = Controller::instance->red * DISCO_STEP_PERCENT;
    float gStep = Controller::instance->green * DISCO_STEP_PERCENT;
    float bStep = Controller::instance->blue * DISCO_STEP_PERCENT;

    fade(rStep, gStep, bStep, 0, 0, 0);
}

void YourDiscoMode::quarters() {
    if (beatCount == 0
        || beatCount == DISCO_QUARTER
        || beatCount == DISCO_QUARTER * 2
        || beatCount == DISCO_QUARTER * 3) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::eigths() {
    if (beatCount == 0
        || beatCount == DISCO_EIGTH
        || beatCount == DISCO_EIGTH * 2
        || beatCount == DISCO_EIGTH * 3
        || beatCount == DISCO_EIGTH * 4
        || beatCount == DISCO_EIGTH * 5
        || beatCount == DISCO_EIGTH * 6
        || beatCount == DISCO_EIGTH * 7) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::stayingAlive() {
    if (beatCount == 0
        || beatCount == DISCO_SIXTEENTH
        || beatCount == DISCO_SIXTEENTH * 2
        || beatCount == DISCO_SIXTEENTH * 3
        || beatCount == DISCO_QUARTER
        || beatCount == DISCO_QUARTER * 2
        || beatCount == DISCO_QUARTER * 2 + DISCO_SIXTEENTH
        || beatCount == DISCO_QUARTER * 2 + DISCO_SIXTEENTH * 2
        || beatCount == DISCO_QUARTER * 2 + DISCO_SIXTEENTH * 3
        || beatCount == DISCO_QUARTER * 3) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::dancingQueen() {
    if (beatCount == 0
        || beatCount == DISCO_QUARTER
        || beatCount == DISCO_QUARTER * 2) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::youAreTheDancingQueen() {
    if (beatCount == 0
        || beatCount == DISCO_SIXTEENTH
        || beatCount == DISCO_SIXTEENTH * 2
        || beatCount == DISCO_SIXTEENTH * 3
        || beatCount == DISCO_QUARTER
        || beatCount == DISCO_QUARTER * 2
        || beatCount == DISCO_QUARTER * 3) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::anotherOneBytesTheDust() {
    if (beatCount == 0
        || beatCount == DISCO_SIXTEENTH
        || beatCount == DISCO_SIXTEENTH * 2
        || beatCount == DISCO_SIXTEENTH * 3
        || beatCount == DISCO_QUARTER
        || beatCount == DISCO_QUARTER + DISCO_EIGTH
        || beatCount == DISCO_QUARTER * 2) {
        writeColor();
    } else
        pass();
}

void YourDiscoMode::YMCA() {
    if (beatCount == 0
        || beatCount == DISCO_HALF
        || beatCount == DISCO_HALF + DISCO_QUARTER
        || beatCount == DISCO_HALF + DISCO_QUARTER + DISCO_EIGTH) {
        writeColor();
    } else
        pass();

}
