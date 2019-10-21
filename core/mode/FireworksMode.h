#ifndef NITELITE_FIREWORKSMODE_H
#define NITELITE_FIREWORKSMODE_H


#include <Mode.h>

class FireworksMode : public Mode {

public:

    FireworksMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

protected:

    Color *color;

    virtual void chooseColor();
};
#endif //NITELITE_FIREWORKSMODE_H
