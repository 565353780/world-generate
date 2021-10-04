#ifndef EASY_TREE_H
#define EASY_TREE_H

#include <iostream>
#include <string>

#include "EasyNode.h"

// Tree Struct :
// World
// Boundary World
// Boundary Line & Space
// Room World
// Room Line & Space
// Furniture World
// Furniture Line & Space

class EasyTree
{
public:
    EasyTree() {}

    bool reset();

    bool createWorld();

    EasyNode* findNode(
        const size_t &id,
        const NodeType &type);

private:
    EasyNode *root_;
};

#endif //EASY_TREE_H
