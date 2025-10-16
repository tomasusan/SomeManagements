#pragma once
#include "../GlobalUtils/Matrix.h"

class CellDetect {
private:
    Matrix<char> *cellMatrix = nullptr;
public:
    CellDetect() = delete;
    CellDetect(const bool loadDefault);
};
