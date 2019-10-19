#ifndef NITELITE_CONFIGSCREEN_H
#define NITELITE_CONFIGSCREEN_H


#include <Screen.h>
#include <oled/Oled.h>

class ConfigScreen : public Screen {

public:
    ConfigScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;
};

#endif //NITELITE_CONFIGSCREEN_H
