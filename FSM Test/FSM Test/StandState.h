#pragma once

#include "BaseState.h"

class StandState : public BaseState {
public:
    void handleInput(char input);
    void update();
};