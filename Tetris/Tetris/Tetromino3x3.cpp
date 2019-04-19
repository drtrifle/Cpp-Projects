#include "pch.h"
#include "Tetromino3x3.h"


Tetromino3x3::Tetromino3x3() {
    tetro.resize(3);
    for (int i = 0; i < 3; ++i) {
        tetro.push_back(std::vector<int>());
        for (int j = 0; j < 3; ++j) {
            tetro[0].push_back(0);
        }
    }

    CreateRandomTetromino();
}


Tetromino3x3::~Tetromino3x3() {
}

void Tetromino3x3::CreateRandomTetromino() {
    switch (CreateRandomNumber(5)) {
        case 0:
            tetro[0][0] = 1;
            tetro[0][0] = 1;
            break;
        
        default:
            break;
    }
}
