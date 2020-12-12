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
    HuffmanTree(const std::string& text);
    ~HuffmanTree();
    
    static std::multimap<int, char> sortedDictionaryOfSymbolsInText(const std::string &text);

private:

};
#endif
