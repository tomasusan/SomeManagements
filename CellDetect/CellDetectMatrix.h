#pragma once
#include "../GlobalUtils/Matrix.h"


class CellDetectMatrix:Matrix<char> {
    CellDetectMatrix() = delete;

public:
    void ShowMatrix() override;

};

inline void CellDetectMatrix::ShowMatrix() {

}
