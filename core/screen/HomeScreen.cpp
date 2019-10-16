#include "HomeScreen.h"
#include "Controller.h"

HomeScreen::HomeScreen(Controller *controller) : Screen(controller) {}

const char *HomeScreen::getName() {
    return "Home";
}

void HomeScreen::enter() {
    Display *display = controller->display;
    display->showHome();
}

void HomeScreen::update() {
    Display *display = controller->display;
}

unsigned long HomeScreen::getIdleTimeout() {
    return 3600000;
}
