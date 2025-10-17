#pragma once
#include <windows.h>
#include "../GlobalUtils/Matrix.h"


class CellDetectMatrix:Matrix<char> {
    CellDetectMatrix() = delete;

public:
    void ShowMatrix() override;

};

inline void CellDetectMatrix::ShowMatrix() {
    for (int i = 0; i < Size; i++) {

        std::cout << LinearMatrix[i] << " ";
        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}

inline void SetColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}