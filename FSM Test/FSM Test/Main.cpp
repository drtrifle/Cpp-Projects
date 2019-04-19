// Program Entry Point

#include <iostream>
#include "hero.h"

int main(int argc, char** argv[]) {
    std::cout << "Testin\n";
    Hero hero1;
    hero1.update();

    char input = 'c';

    hero1.handleInput(input);
    hero1.update();


    return 0;
}