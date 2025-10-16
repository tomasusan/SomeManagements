//
// Created by admin on 25-10-16.
//

#include "TreeManagement.h"

Tree *TreeManagement::ApplyTree(int maximumChild) const {
    int i=0;
    Tree *newTree = nullptr;
    while (true) {
        if (i == maximumTreeNum) break;
        if (TreeSet.contains(i)) {
            i++;
            continue;
        }
        newTree = new Tree(i, maximumTreeNum);
        break;
    }

    return newTree;
}

void TreeManagement::DeleteTree(const Tree *treeToDelete) {
    TreeSet.erase(treeToDelete->treeIndex);
    delete treeToDelete;
}
