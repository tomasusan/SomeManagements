#pragma once
#include <vector>


class TreeNode {
private:
    int index = -1;
    int rootIndex = -1;
    int maxChild = -1;
    TreeNode *father = nullptr;
    std::vector<TreeNode *> children;
public:
    TreeNode() = default;
    TreeNode(int inIndex, int inRootIndex, TreeNode *inFather, int maximumChild = -1);
    void Insert(int inIndex);
    void DeleteNode() const;
    [[nodiscard]] bool IsRoot() const;
    ~TreeNode();
};
