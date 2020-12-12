#include "HuffmanTreeNodes.h"
#include <stdexcept>

HuffmanTreeInnerNode::HuffmanTreeInnerNode(const long &occuranceData, HuffmanTreeNode *left, HuffmanTreeNode *right)
{
    occurance_data = occuranceData;
    _left = left;
    _right = right;
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
    throw std::exception();
}

HuffmanTreeNode *HuffmanTreeInnerNode::left() const
{
    return _left;
}

HuffmanTreeNode *HuffmanTreeInnerNode::right() const
{
    return _right;
}