//
// Created by admin on 25-10-16.
//

#include "CellDetect.h"

#include <utility>

CellDetect::CellDetect(const bool loadDefault) {
    if (loadDefault) {
        LoadDefaultCellMatrix();
    }
}

void CellDetect::LoadDefaultCellMatrix() {
    /** 硬编码32*32 矩阵*/
    const char* DefaultMatrix[32] = {
        "****#####***************######**",
        "***#######*************########*",
        "**#########***********#########*",
        "**#########***********#########*",
        "**#########************#######**",
        "*****####***************#####***",
        "********************************",
        "***#######**********########****",
        "**#########********###########**",
        "**#########********###########**",
        "***#######**********########****",
        "********************************",
        "****########################****",
        "***#######***********########***",
        "**#########***###***##########**",
        "**#########***###***##########**",
        "**#########**********########***",
        "***#########################****",
        "********************************",
        "******#####****###########******",
        "*****#######***###########******",
        "****#########***##############**",
        "***###########***#######*****#**",
        "**############***######******#**",
        "**#############***####*******#**",
        "*****************************#**",
        "****######*******************#**",
        "***########******************#**",
        "**##########*****************#**",
        "**#########*********************",
        "***###########################**",
        "********************************"
    };


    cellMatrix = new CellDetectMatrix(32, 32);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            cellMatrix->SetAt(i, j, DefaultMatrix[i][j]);
            auto newNode = new CellNode{{i, j}};
            newNode->setRoot = newNode;
            nodeMap.insert(std::pair<std::pair<int, int>, CellNode *>({i, j}, newNode));
        }
    }
    matrixSize = {32, 32};
}

void CellDetect::DetectCells() {
    for (int i = 0; i < matrixSize.first; i++) {
        for (int j = 0; j < matrixSize.second; j++) {
            const auto curElement = cellMatrix->GetAt(i, j);
            if (!curElement || *curElement != '#') continue;
            auto it = nodeMap.find(std::pair<int, int>(i, j));
            const auto curNode = it->second;

            // 孤立的尚未标记的结点
            if (FindRoot(curNode)->setIndex == -1) {
                curNode->setRoot = nullptr;
                curNode->setIndex = AddSet(curNode->location);
            }

            // 八向结点传递
            for (int k = 0; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;
                    auto neighbourElement = cellMatrix->GetAt(i + k, j + l);
                    //std::cout << *neighbourElement << std::endl;
                    if (!neighbourElement || *neighbourElement != '#') continue;

                    it = nodeMap.find(std::pair<int, int>(i + k, j + l));
                    const auto neighbourNode = it->second;
                    if (FindRoot(curNode)->setIndex == FindRoot(neighbourNode)->setIndex) continue;

                    if (FindRoot(neighbourNode)->setIndex == -1) {
                        // 未标记的结点，直接并入当前结点集合
                        neighbourNode->setRoot = FindRoot(curNode);
                    } else if (FindRoot(curNode)->setIndex != FindRoot(neighbourNode)->setIndex) {
                        // 已标记的不同集合的结点，对邻居结点的根节点进行合并
                        cellSet.erase(FindRoot(neighbourNode)->setIndex);
                        FindRoot(neighbourNode)->setRoot = FindRoot(curNode);
                    }
                }
            }
        }
    }

    for (int i=0;i<matrixSize.first;i++) {
        for (int j=0;j<matrixSize.second;j++) {
            auto curElement = cellMatrix->GetAt(i, j);
            if (!curElement || *curElement != '#') continue;
            auto it = nodeMap.find(std::pair<int, int>(i, j));
            auto curNode = it->second;
            cellMatrix->SetAt(i, j, '0' + FindRoot(curNode)->setIndex);
        }
    }

    std::cout << "Find Cells: " << cellSet.size() << std::endl;
    cellMatrix->ShowMatrix();
    return;
}

CellNode *CellDetect::FindRoot(CellNode *node) {
    auto curNode = node;
    while (curNode->setRoot) {
        if (curNode == curNode->setRoot) return curNode;
        curNode = curNode->setRoot;
    }
    return curNode;
}

int CellDetect::AddSet(std::pair<int, int> root) {
    setCount++;
    cellSet.insert(setCount);
    return setCount;
}
