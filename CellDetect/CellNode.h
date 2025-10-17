#pragma once
#include <utility>

class CellNode {
public:
    std::pair<int, int> location = {-1, -1};
    CellNode *setRoot = nullptr;
    /** 所属集合编号，仅在root结点有效，其余结点通过FindRoot()方法查找集合编号*/
    int setIndex = -1;
};
