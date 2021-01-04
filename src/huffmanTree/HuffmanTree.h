#ifndef _HUFFMAN_TREE_HH_
#define _HUFFMAN_TREE_HH_

#include <functional>
#include <unordered_map>
#include <queue>
#include <string>

#include "HuffmanTreeNodes.h"

/**
 * Tree used for compression and decompression of strings, created from <char,int> unordered_map
*/
class HuffmanTree
{
private:
    HuffmanTreeNode *root;

public:
    /**
     * Constructor with <char,int> unordered_map
    */
    HuffmanTree(const std::unordered_map<char, int> &dictionary);
    ~HuffmanTree();

    /**
     * Converts text to binary string based on built huffman tree
    */
    std::string convertToBinary(const std::string &) const;

    /**
     * Converts binary to text based on built huffman tree
    */
    std::string convertFromBinary(const std::string &) const;

private:
    /**
     * Creation utilities
    */
    struct NodeWrapper
    {
        HuffmanTreeNode *node;
        int order;
    };
    
    using NodeComparator = std::function<bool(NodeWrapper, NodeWrapper)>;
    static const NodeComparator nodeComparator;
    using NodePriorityQueue = std::priority_queue<NodeWrapper, std::vector<NodeWrapper>, NodeComparator>;

    std::unordered_map<char, std::string> generateReplacementBinaryCodes() const;
    void generateReplacementBinaryCodesHelper(HuffmanTreeNode *currentNode, const std::string &currentReplacementString, std::unordered_map<char, std::string> &) const;
};

#endif
