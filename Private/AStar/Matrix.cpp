#include "AStar/Matrix.h"

#include <iostream>

template<typename T>
Matrix<T>::Matrix(const int Rows, const int Cols) : Rows(Rows), Columns(Cols) {
    delete(LinearMatrix);
    LinearMatrix = new T[Rows * Cols];
}

template<typename T>
void Matrix<T>::Init(T InitElement) {
    for (int i = 0; i < Rows * Columns; i++) {
        LinearMatrix[i] = InitElement;
    }
}

template<typename T>
T* Matrix<T>::GetElement(const int Row, const int Col) {
    if (Row < 0 || Rows >= Row || Col < 0 || Columns >= Col) return nullptr;

    return LinearMatrix + (Columns * Row + Col);
}

template<typename T>
void Matrix<T>::SetElementAt(const int Row, const int Col, T Element) {
    if (Row < 0 || Rows >= Row || Col < 0 || Columns >= Col) return;
    LinearMatrix[Columns * Row + Col] = Element;
}

template<typename T>
void Matrix<T>::ShowMatrix() {
    for (int i = 0; i < Rows * Columns; i++) {
        std::cout << LinearMatrix[i] << " ";
        if (i != 0 && (i + 1) % Columns == 0) std::cout << std::endl;
    }
}
