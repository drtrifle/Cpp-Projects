#include <cctype>

#include "Hero.h"

void Hero::handleInput(char &input) {
   
    input = toupper(input);

    currState->handleInput(input);
}

void Hero::update() {
    currState->update();
}
