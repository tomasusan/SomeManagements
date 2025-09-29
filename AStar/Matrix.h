#pragma once

template<typename T>
class Matrix {
public:
    Matrix(int InRow, int InCol);
    ~Matrix();

    void SetAt(int AtRow, int AtCol, T InElement);
    T* GetAt(int AtRow, int AtCol);
    void ShowMatrix();

private:
    T* LinearMatrix;
    int Row, Col;
    int Size = 0;
};
