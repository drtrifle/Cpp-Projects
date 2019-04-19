#pragma once

#include "BaseState.h"

class CrouchState : public BaseState {
public:
    void handleInput(char input);
    void update();
};

