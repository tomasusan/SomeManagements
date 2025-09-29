#pragma once
#include "Matrix.h"
#include "LogManagement.h"

class AStarMatrix : public Matrix<char> {
public:
    AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart, const std::pair<int, int> &InEnd,
                bool LoadDefault);

private:
    std::pair<int, int> Start, End;

    void LoadDefaultMatrix();
    virtual void ShowMatrix() override;
};

inline AStarMatrix::AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart,
                                const std::pair<int, int> &InEnd, bool LoadDefault): Matrix<char>(0, 0) {
    if (LoadDefault) {
        LoadDefaultMatrix();
    } else {
        ResizeMatrix(InRow, InCol);
        Start = InStart;
        End = InEnd;
    }
}

inline void AStarMatrix::LoadDefaultMatrix() {
    const char *DefaultMatrix[] = {
        "********",
        "*S**#***",
        "****#***",
        "****#***",
        "****#***",
        "**###*E*",
        "****#***",
        "********"
    };

    ResizeMatrix(8, 8);

    LogManagement::GetInstance()->Display("Init Default", "AStarMatrix");
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            SetAt(i, j, DefaultMatrix[i][j]);
            if (DefaultMatrix[i][j] == 'S') Start = {i, j};
            if (DefaultMatrix[i][j] == 'E') End = {i, j};
        }
}

inline void AStarMatrix::ShowMatrix() {
    Matrix<char>::ShowMatrix();
}
