#pragma once

template<typename T>
class Matrix {
private:
    T* LinearMatrix;
    int Rows;
    int Columns;

public:
    Matrix(int Rows, int Cols);

    virtual void Init(T InitElement);

    T* GetElement(int Row, int Col);
    void SetElementAt(int Row, int Col, T Element);

    void ShowMatrix();
};
