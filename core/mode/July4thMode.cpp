#include <Controller.h>
#include "July4thMode.h"

July4thMode::July4thMode() : FireworksMode() {

}

const char *July4thMode::getName() {
    return "4th of July";
}

void July4thMode::chooseColor() {
    long choice = Controller::instance->hardware->randomLong(3);
    if(choice == 0) {
        color->r = 255;
        color->g = 0;
        color->b = 0;
    } else if(choice == 1) {
        color->r = 255;
        color->g = 255;
        color->b = 255;
    } else {
        color->r = 0;
        color->g = 0;
        color->b = 255;
    }

}
