#pragma once
#include "TreeNode.h"
#include <map>

class Tree {
private:
    TreeNode *root = nullptr;
    bool validated = false;
    std::map<int, TreeNode *> nodeMap;

public:
    int treeIndex = -1;

private:
    [[nodiscard]] bool ValidateTree();

public:
    Tree() = delete;
    explicit Tree(int inTreeIndex, int maximumChild = -1);
    void InsertAt(int index);
    TreeNode *FindNode(int index);
    ~Tree();
};
