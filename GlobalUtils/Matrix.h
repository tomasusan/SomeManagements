#pragma once

#include <iostream>

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 矩阵基类
 * @details 通过一维矩阵模拟二维矩阵行为，不支持[][]访问方法
 * @tparam T 矩阵元素模板
 */
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

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 设置指定位置元素
 * @param AtRow 查找行
 * @param AtCol 查找列
 * @param InElement 设置元素
 */
template<typename T>
void Matrix<T>::SetAt(int AtRow, int AtCol, T InElement) {
    if (AtRow < 0 || AtRow >= Row || AtCol < 0 || AtCol >= Col) return;
    LinearMatrix[AtRow * Col + AtCol] = InElement;
}

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 查找指定位置元素
 * @param AtRow 查找行
 * @param AtCol 查找列
 * @return 指定位置元素指针，越界时为空指针
 */
template<typename T>
T* Matrix<T>::GetAt(int AtRow, int AtCol) {
    if (AtRow < 0 || AtRow >= Row || AtCol < 0 || AtCol >= Col) return nullptr;
    return LinearMatrix + AtRow * Col + AtCol;
}

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 打印矩阵
 */
template<typename T>
void Matrix<T>::ShowMatrix() {
    for (int i = 0; i < Size; i++) {
        std::cout << LinearMatrix[i] << " ";
        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 重新定义矩阵空间
 * @param InRow 行数
 * @param InCol 列数
 */
template<typename T>
void Matrix<T>::ResizeMatrix(int InRow, int InCol) {
    delete[] LinearMatrix;
    LinearMatrix = new T[InRow * InCol];
    Row = InRow;
    Col = InCol;
    Size = InRow * InCol;
}
