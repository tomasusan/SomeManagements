#pragma once

#include <iostream>

template<typename T>
class Matrix {
public:
    Matrix(int InRow, int InCol);

    virtual ~Matrix();

    void SetAt(int AtRow, int AtCol, T InElement);
    T* GetAt(int AtRow, int AtCol);
   virtual void ShowMatrix();

private:

    T* LinearMatrix;
protected:
    void ResizeMatrix(int InRow, int InCol);
    int Row, Col;
    int Size = 0;
};

template<typename T>
Matrix<T>::Matrix(int InRow, int InCol) {
    LinearMatrix = new T[InRow * InCol];
    Size = InRow * InCol;
    Row = InRow;
    Col = InCol;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] LinearMatrix;
}

template<typename T>
void Matrix<T>::SetAt(int AtRow, int AtCol, T InElement) {
    if (AtRow < 0 || AtRow >= Row || AtCol < 0 || AtCol >= Col) return;
    LinearMatrix[AtRow * Col + AtCol] = InElement;
}

template<typename T>
T* Matrix<T>::GetAt(int AtRow, int AtCol) {
    if (AtRow < 0 || AtRow >= Row || AtCol < 0 || AtCol >= Col) return nullptr;
    return LinearMatrix + AtRow * Col + AtCol;
}

template<typename T>
void Matrix<T>::ShowMatrix() {
    for (int i = 0; i < Size; i++) {
        std::cout << LinearMatrix[i] << " ";
        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}

template<typename T>
void Matrix<T>::ResizeMatrix(int InRow, int InCol) {
    delete[] LinearMatrix;
    LinearMatrix = new T[InRow * InCol];
    Row = InRow;
    Col = InCol;
    Size = InRow * InCol;
}
