#pragma once

#include <vector>

class Tetromino {
public:
    Tetromino();
    ~Tetromino();
protected:
    virtual void CreateRandomTetromino();

    int CreateRandomNumber(int range);
    std::vector<std::vector<int>> tetro;
};

