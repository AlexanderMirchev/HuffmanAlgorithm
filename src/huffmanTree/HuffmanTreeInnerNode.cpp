#include "HuffmanTreeNodes.h"
#include <stdexcept>

HuffmanTreeInnerNode::HuffmanTreeInnerNode(HuffmanTreeNode *left, HuffmanTreeNode *right)
{
    occurance_data = left->occuranceData() + right->occuranceData();
    _left = left;
    _right = right;
    _height = std::max(left->height(), right->height()) + 1;
}

HuffmanTreeInnerNode::~HuffmanTreeInnerNode()
{
    delete _left;
    delete _right;
}

bool HuffmanTreeInnerNode::isLeaf() const
{
    return false;
}

const long &HuffmanTreeInnerNode::occuranceData() const
{
    return this->occurance_data;
}

const char &HuffmanTreeInnerNode::characterData() const
{
    throw HuffmanTreeExceptions::TreeNodeBadAccess();
}

HuffmanTreeNode *HuffmanTreeInnerNode::left() const
{
    return _left;
}

HuffmanTreeNode *HuffmanTreeInnerNode::right() const
{
    return _right;
}

int HuffmanTreeInnerNode::height() const
{
    return _height;
}
