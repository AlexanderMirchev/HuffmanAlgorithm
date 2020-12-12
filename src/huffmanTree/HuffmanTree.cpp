#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include <stdexcept>
#include <queue>
#include <algorithm>

HuffmanTree::HuffmanTree(const std::unordered_map<char, int> &dictionary) : root{nullptr}
{
    const std::multimap<int, char> sortedDictionary = HuffmanTreeHelper::sortDictionary(dictionary);

    // TODO put left and right

    for (auto sortedPair : sortedDictionary)
    {
        if (!root)
        {
            root = new HuffmanTreeLeaf(sortedPair.first, sortedPair.second);
        }
        else
        {
            root = new HuffmanTreeInnerNode(
                root->occuranceData() + sortedPair.first,
                new HuffmanTreeLeaf(sortedPair.first, sortedPair.second),
                root);
        }
    }
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
    generateRepalcementBinaryCodesHelper(root, "", replacementBinaryCodes);
    return replacementBinaryCodes;
}

void HuffmanTree::generateRepalcementBinaryCodesHelper(HuffmanTreeNode *node, const std::string &currentReplacementString, std::unordered_map<char, std::string> &map) const
{

    if (node->isLeaf())
    {
        map[node->characterData()] = currentReplacementString;
    }
    else
    {
        generateRepalcementBinaryCodesHelper(node->left(), currentReplacementString + '0', map);
        generateRepalcementBinaryCodesHelper(node->right(), currentReplacementString + '1', map);
    }
}
