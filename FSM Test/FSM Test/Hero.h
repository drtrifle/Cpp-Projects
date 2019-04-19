#pragma once

#include "StandState.h"

class Hero {
private:
    BaseState* currState;

public:
    Hero() {
        currState = new StandState();
    }

    ~Hero() {
        delete currState;
    }

    //Input is an int for now
    virtual void handleInput(char &input);

    virtual void update();
};