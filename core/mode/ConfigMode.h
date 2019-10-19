#ifndef NITELITE_CONFIGMODE_H
#define NITELITE_CONFIGMODE_H


#include <Mode.h>

class ConfigMode : public Mode {

public:

    ConfigMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;
};

#endif //NITELITE_CONFIGMODE_H
