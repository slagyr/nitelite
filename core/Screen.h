#ifndef NITELITE_SCREEN_H
#define NITELITE_SCREEN_H

class Controller;

class Screen {
public:
    virtual ~Screen() = default;;

    virtual const char *getName() = 0;

    virtual void enter() = 0;

    virtual void update() = 0;

protected:
    explicit Screen(Controller *controller) {
        this->controller = controller;
    };

    Controller *controller;
};


#endif //NITELITE_SCREEN_H
