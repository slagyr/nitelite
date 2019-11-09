#include "SplashScreen.h"
#include "Controller.h"
#include "splash.h"
#include <oled/OledFonts.h>

const char *SplashScreen::getName() {
    return "Splash";
}

void SplashScreen::enter() {
    Controller::instance->display->drawBitmap(0, 0, 128, 64, splashBMP);
    Controller::instance->display->setFont(oled_font6x8);
    Controller::instance->display->writeString(20, 7, "NiteLite 1.0");
}

void SplashScreen::update() {

}

SplashScreen::SplashScreen() : Screen() {}

