#pragma once

#include "Tetromino.h"

class Tetromino3x3 : public Tetromino {
public:
    Tetromino3x3();
    ~Tetromino3x3();
protected:
    void CreateRandomTetromino() override;
};

