#ifndef NITELITE_RGBSCREEN_H
#define NITELITE_RGBSCREEN_H


#include <Screen.h>

class RGBScreen : public Screen {

public:
    RGBScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;

    unsigned long getIdleTimeout() override;
};


#endif //NITELITE_RGBSCREEN_H
