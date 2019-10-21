#ifndef NITELITE_WANDERMODE_H
#define NITELITE_WANDERMODE_H


#include <Mode.h>

class WanderMode : public Mode {

public:

    WanderMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    Color *dest;
    float rStep;
    float gStep;
    float bStep;

    void chooseDest();
};

#endif //NITELITE_WANDERMODE_H
