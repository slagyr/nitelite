#ifndef NITELITE_SPLASHSCREEN_H
#define NITELITE_SPLASHSCREEN_H


#include <Screen.h>

class SplashScreen : public Screen {

public:
    explicit SplashScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;

};


#endif //NITELITE_SPLASHSCREEN_H
