#include "RGBScreen.h"
#include "Controller.h"

RGBScreen::RGBScreen(Controller *controller) : Screen(controller) {}

const char *RGBScreen::getName() {
    return "RGB";
}

void RGBScreen::enter() {
    Display *display = controller->display;
    display->showHome();
}

void RGBScreen::update() {
    Display *display = controller->display;
}

unsigned long RGBScreen::getIdleTimeout() {
    return 3600000;
}
