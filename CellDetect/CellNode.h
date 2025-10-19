#pragma once
#include <utility>

/**
 * @author tomasusan
 * @date 2025-10-16
 * @brief 结点类，存储当前位置，并且标记集合根节点
 */
class CellNode {
public:
    /** 当前位置*/
    std::pair<int, int> location = {-1, -1};
    /** 所属集合根节点，孤立结点的root为其自身*/
    CellNode *setRoot = nullptr;
    /** 所属集合编号，仅在root结点有效，其余结点通过FindRoot()方法查找集合编号*/
    int setIndex = -1;
};
