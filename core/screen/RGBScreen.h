#ifndef NITELITE_RGBSCREEN_H
#define NITELITE_RGBSCREEN_H


#include <Screen.h>
#include <oled/Oled.h>

class RGBScreen : public Screen {

public:
    RGBScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;

    void writeColorValue(int row, const char *colorVal) const;
};


#endif //NITELITE_RGBSCREEN_H
