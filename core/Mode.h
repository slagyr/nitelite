#ifndef NITELITE_MODE_H
#define NITELITE_MODE_H

class Controller;

class Mode {
public:
    virtual ~Mode() = default;

    virtual const char *getName() = 0;

    virtual void enter() = 0;

    virtual void tick() = 0;

protected:
    explicit Mode(Controller *controller) {
        this->controller = controller;
    };

    Controller *controller;
};

#endif //NITELITE_MODE_H
