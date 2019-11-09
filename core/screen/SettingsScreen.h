#ifndef NITELITE_SETTINGSSCREEN_H
#define NITELITE_SETTINGSSCREEN_H


#include <Screen.h>
#include <oled/Oled.h>

class SettingsScreen : public Screen {

public:
    SettingsScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;
};


#endif //NITELITE_SETTINGSSCREEN_H
