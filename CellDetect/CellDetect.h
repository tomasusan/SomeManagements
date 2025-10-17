#pragma once
#include "CellNode.h"
#include <map>
#include <set>
#include "../GlobalUtils/Matrix.h"

struct Node {
    int rootIndex = -1;
};

class CellDetect {
private:
    Matrix<char> *cellMatrix = nullptr;
    std::pair<int, int> matrixSize = {-1, -1};
    std::set<int> cellSet;
    int setCount = 0;
    std::map<std::pair<int, int>, CellNode*> nodeMap;
public:
    CellDetect() = delete;

    explicit CellDetect(bool loadDefault);
    void LoadDefaultCellMatrix();
    void DetectCells();

    CellNode *FindRoot(CellNode *node);
    int AddSet(std::pair<int, int> root);
};
