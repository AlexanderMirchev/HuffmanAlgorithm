#include "HuffmanTreeNodes.h"
#include <stdexcept>

HuffmanTreeLeaf::HuffmanTreeLeaf(const long &occuranceData, char characterData)
{
    occurance_data = occuranceData;
    character_data = characterData;
}

bool HuffmanTreeLeaf::isLeaf() const
{
    return true;
}

const long &HuffmanTreeLeaf::occuranceData() const
{
    return this->occurance_data;
}

const char &HuffmanTreeLeaf::characterData() const
{
    return this->character_data;
}

HuffmanTreeNode *HuffmanTreeLeaf::left() const
{
    // TODO
    throw std::exception();
}

HuffmanTreeNode *HuffmanTreeLeaf::right() const
{
    // TODO
    throw std::exception();
}
