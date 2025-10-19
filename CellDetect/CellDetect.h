#pragma once
#include "CellNode.h"
#include <map>
#include <set>

#include "CellDetectMatrix.h"
#include "../GlobalUtils/Matrix.h"

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 并查集连通区域查找实现类
 */
class CellDetect {
private:
    CellDetectMatrix *cellMatrix = nullptr;
    std::pair<int, int> matrixSize = {-1, -1};
    std::set<int> cellSet;
    std::set<CellNode *> rootSet;
    std::map<int, CellNode *> rootMap;
    int setCount = 0;
    std::map<std::pair<int, int>, CellNode*> nodeMap;
public:
    CellDetect() = delete;

    explicit CellDetect(bool loadDefault);
    void LoadDefaultCellMatrix();
    void DetectCells(bool seeOnlyRoot = false);

    CellNode *FindRoot(CellNode *node);
    int AddSet(std::pair<int, int> root);
    std::map<int, int> CreateMap() const;
};
