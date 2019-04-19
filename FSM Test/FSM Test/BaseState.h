#pragma once

class BaseState {
public:
    virtual void handleInput(char input); 
    virtual void update();
};