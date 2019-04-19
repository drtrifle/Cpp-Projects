#include "pch.h"
#include "Tetromino4x4.h"


Tetromino4x4::Tetromino4x4() {
    tetro.resize(4);
    for (int i = 0; i < 4; ++i) {
        tetro.push_back(std::vector<int>());
        for (int j = 0; j < 4; ++j) {
            tetro[0].push_back(0);
        }
    }
}


Tetromino4x4::~Tetromino4x4() {
}
