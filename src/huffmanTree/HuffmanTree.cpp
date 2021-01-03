#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include "HuffmanTreeExceptions.h"

#include <iostream>
#include <stdexcept>


HuffmanTree::HuffmanTree(const std::unordered_map<char, int> &dictionary) : root{nullptr}
{
    NodePriorityQueue nodePriorityQueue(nodeComparator);

    for (auto pair : dictionary)
    {
        nodePriorityQueue.push({new HuffmanTreeLeaf(pair.second, pair.first), 0});
    }

    int order = 1;
    while (nodePriorityQueue.size() >= 2)
    {
        HuffmanTreeNode *left = nodePriorityQueue.top().node;
        nodePriorityQueue.pop();

        HuffmanTreeNode *right = nodePriorityQueue.top().node;
        nodePriorityQueue.pop();

        nodePriorityQueue.push({new HuffmanTreeInnerNode(left, right), order++});
    }

    root = nodePriorityQueue.top().node;
}

HuffmanTree::~HuffmanTree()
{
    delete root;
}

std::string HuffmanTree::convertToBinary(const std::string &text) const
{
    std::string binaryResult;

    std::unordered_map<char, std::string> replacementBinaryCodes = generateReplacementBinaryCodes();
    for (auto symbol : text)
    {
        binaryResult.append(replacementBinaryCodes[symbol]);
    }

    return binaryResult;
}

std::string HuffmanTree::convertFromBinary(const std::string &binary) const
{
    std::string result;

    HuffmanTreeNode *searchingNode = root;

    for (auto elem : binary)
    {
        if (elem == '0')
        {
            searchingNode = searchingNode->left();
        }
        else if (elem == '1')
        {
            searchingNode = searchingNode->right();
        }
        else
        {
            throw HuffmanTreeExceptions::BadSerializedInput();
        }
        

        if (searchingNode->isLeaf())
        {
            result.push_back(searchingNode->characterData());
            searchingNode = root;
        }
    }

    return result;
}

std::unordered_map<char, std::string> HuffmanTree::generateReplacementBinaryCodes() const
{
    std::unordered_map<char, std::string> replacementBinaryCodes;
    generateReplacementBinaryCodesHelper(root, "", replacementBinaryCodes);
    return replacementBinaryCodes;
}

void HuffmanTree::generateReplacementBinaryCodesHelper(HuffmanTreeNode *node, const std::string &currentReplacementString, std::unordered_map<char, std::string> &map) const
{

    if (node->isLeaf())
    {
        map[node->characterData()] = currentReplacementString;
    }
    else
    {
        generateReplacementBinaryCodesHelper(node->left(), currentReplacementString + '0', map);
        generateReplacementBinaryCodesHelper(node->right(), currentReplacementString + '1', map);
    }
}

const HuffmanTree::NodeComparator HuffmanTree::nodeComparator = [](NodeWrapper m, NodeWrapper n) -> bool {
    if (m.node->occuranceData() == n.node->occuranceData())
    {
        if (m.node->isLeaf() && n.node->isLeaf())
        {
            return m.node->characterData() > n.node->characterData();
        }
        else if (m.node->height() != n.node->height())
        {
            return m.node->height() < n.node->height();
        }
        else
        {
            return m.order > n.order;
        }
    }

    return m.node->occuranceData() > n.node->occuranceData();
};
