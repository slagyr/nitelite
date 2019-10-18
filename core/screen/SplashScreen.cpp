#include "SplashScreen.h"
#include "Controller.h"
#include "splash.h"
#include <oled/OledFonts.h>

const char *SplashScreen::getName() {
    return "Splash";
}

void SplashScreen::enter() {
    controller->display->drawBitmap(0, 0, 128, 64, splashBMP);
    controller->display->setFont(oled_font6x8);
    controller->display->writeString(20, 7, "NiteLite 1.0");
    controller->display->show();
}

void SplashScreen::update() {

}

SplashScreen::SplashScreen(Controller *controller) : Screen(controller) {}

