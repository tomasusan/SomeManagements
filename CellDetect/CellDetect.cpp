#include "CellDetect.h"

#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 构造函数
 * @param loadDefault 是否加载默认矩阵
 */
CellDetect::CellDetect(const bool loadDefault) {
    if (loadDefault) {
        LoadDefaultCellMatrix();
    }
}

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 加载默认硬编码矩阵
 */
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
        "**#########*######***########***",
        "**#########*######***#########**",
        "**#########**********########***",
        "***#########################****",
        "********************************",
        "******#####****###########******",
        "*****#######***###########******",
        "****#########***##############**",
        "***###########***#######*****#**",
        "**############***#############**",
        "**#############***####*******#**",
        "*****************************#**",
        "****######****###########****#**",
        "***########**##*##########***#**",
        "**##########*##**##########**#**",
        "**#########******************#**",
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

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 并查集实现函数
 * @param seeOnlyRoot 仅根节点视图
 */
void CellDetect::DetectCells(bool seeOnlyRoot) {
    cellMatrix->ShowMatrix();
    std :: cout << "Start Cell Detecting..." << std::endl;
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
                rootSet.insert(curNode);
                rootMap.insert(std::pair(curNode->setIndex, curNode));
            }

            // 六向结点传递，由于从上向下扫描，所以没有必要回扫上方的结点
            for (int k = 0; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;
                    const auto neighbourElement = cellMatrix->GetAt(i + k, j + l);
                    if (!neighbourElement || *neighbourElement != '#') continue;

                    it = nodeMap.find(std::pair<int, int>(i + k, j + l));
                    const auto neighbourNode = it->second;
                    // 同源结点
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

    auto idMap = CreateMap();

    for (int i=0;i<matrixSize.first;i++) {
        for (int j=0;j<matrixSize.second;j++) {
            auto curElement = cellMatrix->GetAt(i, j);
            if (!curElement || *curElement != '#') continue;
            auto it = nodeMap.find(std::pair<int, int>(i, j));
            auto curNode = it->second;
            if (seeOnlyRoot) cellMatrix->SetAt(i, j, 'A' + curNode->setIndex);
            else cellMatrix->SetAt(i, j, 'A' + idMap[FindRoot(curNode)->setIndex]);
        }
    }

    std::cout << "Find Cells: " << cellSet.size() << std::endl;
    cellMatrix->ShowMatrix();
    return;
}

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 根据链形结构查找集合根节点
 * @param node 需要查找的结点
 * @return 所查找的结点的集合根结点
 */
CellNode *CellDetect::FindRoot(CellNode *node) {
    auto curNode = node;
    while (curNode->setRoot) {
        if (curNode == curNode->setRoot) return curNode;
        curNode = curNode->setRoot;
    }
    return curNode;
}

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 产生一个合法集合
 * @param root 指定根节点
 * @return 该集合id
 */
int CellDetect::AddSet(std::pair<int, int> root) {
    setCount++;
    cellSet.insert(setCount);
    return setCount;
}

/**
 * @author tomasusan
 * @date 2025-10-19
 * @breif 对现有的非连续有序的setIndex集进行映射排序，产生有序连续的id序列，使得输出有序
 * @return id映射
 */
std::map<int, int> CellDetect::CreateMap() const {
    std::vector<int> cacheId;
    for (auto index:cellSet) {
        cacheId.push_back(index);
    }
    std::ranges::sort(cacheId);
    std::map<int, int> map;
    for (int i=0;i<cacheId.size();i++) {
        map.insert(std::pair<int, int>(cacheId[i], i));
    }
    return map;
}

