#ifndef NITELITE_YOURCOLORMODE_H
#define NITELITE_YOURCOLORMODE_H

#include <Mode.h>

class YourColorMode : public Mode {

public:

    YourColorMode();

    const char *getName() override;

    void enter() override;

    void tick() override;
};


#endif //NITELITE_YOURCOLORMODE_H
