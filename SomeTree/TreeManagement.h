#pragma once
#include "Singleton.h"
#include <set>
#include "Tree.h"

#include "TreeNode.h"


class TreeManagement: public Singleton<TreeManagement> {
private:
    std::set<int> TreeSet;
    int maximumTreeNum = 100;

public:
    [[nodiscard]] Tree* ApplyTree(int maximumChild = -1) const;
    void DeleteTree(const Tree *treeToDelete);
};
