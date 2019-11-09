#include <Controller.h>
#include "RGBDiscoMode.h"

const char *RGBDiscoMode::getName() {
    return "Multicolor Disco";
}

void RGBDiscoMode::chooseColor() {
    randomBrightColor(color);
}

RGBDiscoMode::RGBDiscoMode() : YourDiscoMode() {

}
