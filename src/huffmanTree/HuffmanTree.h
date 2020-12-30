#ifndef _HUFFMAN_TREE_HH_
#define _HUFFMAN_TREE_HH_

#include <map>
#include <unordered_map>
#include <string>

#include "HuffmanTreeNodes.h"

class HuffmanTree
{
private:
    HuffmanTreeNode *root;

public:
    HuffmanTree(const std::unordered_map<char, int> &dictionary);
    ~HuffmanTree();

    std::string convertToBinary(const std::string &) const;
    std::string convertFromBinary(const std::string &) const;

private:
    std::unordered_map<char, std::string> generateReplacementBinaryCodes() const;
    void generateRepalcementBinaryCodesHelper(HuffmanTreeNode *currentNode, const std::string &currentReplacementString, std::unordered_map<char, std::string> &) const;
};

#endif
