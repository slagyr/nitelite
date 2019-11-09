#ifndef NITELITE_SETTINGSMODE_H
#define NITELITE_SETTINGSMODE_H


#include <Mode.h>

class SettingsMode : public Mode {

public:

    SettingsMode();

    const char *getName() override;

    void enter() override;

    void tick() override;

    Screen *settingsScreen;
};

#endif //NITELITE_SETTINGSMODE_H
