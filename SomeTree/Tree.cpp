//
// Created by admin on 25-10-16.
//

#include "Tree.h"

#include <stdexcept>

#include "TreeManagement.h"
#include "LogManagement.h"

Tree::Tree(const int inTreeIndex, int maximumChild) {
    try {
        if (inTreeIndex < 0) throw std::runtime_error("Tree index out of range");
        treeIndex = inTreeIndex;
        root = new TreeNode(-1, inTreeIndex, nullptr, maximumChild);
        if (!ValidateTree()) throw std::runtime_error("Invalid Tree");
    } catch (std::exception &e) {
        LogManagement::GetInstance()->Error(e.what(), "BuildTree");
    }
}

void Tree::InsertAt(int index) {
    try{
        const auto nodeIt = nodeMap.find(index);
        if (nodeIt == nodeMap.end()) throw std::runtime_error("Node not found");


    }catch (std::exception &e) {
        LogManagement::GetInstance()->Error(e.what(), "Tree");
    }
}

TreeNode *Tree::FindNode(int index) {
    TreeNode *ret = nullptr;

    return ret;
}

Tree::~Tree() {
    root->DeleteNode();
}

bool Tree::ValidateTree() {
    if (!root) validated = false;
    else validated = true;

    return validated;
}
