#ifndef NITELITE_YOURHEARTBEATMODE_H
#define NITELITE_YOURHEARTBEATMODE_H

#include <Mode.h>

class YourHeartbeatMode : public Mode {

public:

    YourHeartbeatMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    bool up;
    float multiplier;
};


#endif //NITELITE_YOURHEARTBEATMODE_H
