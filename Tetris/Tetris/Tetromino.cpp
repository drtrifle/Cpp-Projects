#include "pch.h"
#include "Tetromino.h"

#include <cstdlib> 
#include <ctime> 

Tetromino::Tetromino() {
}


Tetromino::~Tetromino() {
}

void Tetromino::CreateRandomTetromino() {

}
int Tetromino::CreateRandomNumber(int range) {
    int random_integer;
    for (int index = 0; index < 20; index++) {
        return random_integer = (rand() % range);
    }
}
