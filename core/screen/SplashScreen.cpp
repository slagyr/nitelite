#include "SplashScreen.h"
#include "Controller.h"

const char *SplashScreen::getName() {
    return "Splash";
}

void SplashScreen::enter() {
    controller->display->splash();
}

void SplashScreen::update() {

}

unsigned long SplashScreen::getIdleTimeout() {
    return 3000;
}

SplashScreen::SplashScreen(Controller *controller) : Screen(controller) {}

