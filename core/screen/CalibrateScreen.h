#ifndef NITELITE_CALIBRATESCREEN_H
#define NITELITE_CALIBRATESCREEN_H


#include <Screen.h>
#include <oled/Oled.h>

class CalibrateScreen : public Screen {

public:
    CalibrateScreen();

    const char *getName() override;

    void enter() override;

    void update() override;
};

#endif //NITELITE_CALIBRATESCREEN_H
