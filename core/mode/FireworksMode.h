#ifndef NITELITE_FIREWORKSMODE_H
#define NITELITE_FIREWORKSMODE_H


#include <Mode.h>

class FireworksMode : public Mode {

public:

    FireworksMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    Color *color;
};
#endif //NITELITE_FIREWORKSMODE_H
