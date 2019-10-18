#include "SplashScreen.h"
#include "Controller.h"
#include "splash.h"

const char *SplashScreen::getName() {
    return "Splash";
}

void SplashScreen::enter() {
    controller->display->drawBitmap(0, 0, 128, 64, splashBMP);
}

void SplashScreen::update() {

}

unsigned long SplashScreen::getIdleTimeout() {
    return 3000;
}

SplashScreen::SplashScreen(Controller *controller) : Screen(controller) {}

