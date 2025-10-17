#pragma once
#include <windows.h>
#include "../GlobalUtils/Matrix.h"

enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

class CellDetectMatrix:public Matrix<char> {
    CellDetectMatrix() = delete;
public:
    CellDetectMatrix(int inRow, int inCol): Matrix<char>(inRow, inCol) {

    }

public:
    void ShowMatrix() override;

};

inline void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void CellDetectMatrix::ShowMatrix() {
    for (int i = 0; i < Size; i++) {

        if (LinearMatrix[i] != '*') {
            auto color = (LinearMatrix[i] - '0') % 16;
            if (color == 7) color = 9;
            setColor(color);
        }
        std::cout << LinearMatrix[i] << " ";

        setColor(WHITE);

        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}