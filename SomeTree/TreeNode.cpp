

#include "TreeNode.h"

TreeNode::TreeNode(const int inIndex, const int inRootIndex, TreeNode *inFather, int maximumChild) {
    index = inIndex;
    rootIndex = inRootIndex;
    father = inFather;
    maxChild = maximumChild;
}

void TreeNode::Insert(int inIndex) {
}

void TreeNode::DeleteNode() const {
    delete this;
}

bool TreeNode::IsRoot() const {
    return rootIndex == -1 && !father;
}

TreeNode::~TreeNode() {
    delete father;
    for (const auto child:children) {
        child->DeleteNode();
    }
}
