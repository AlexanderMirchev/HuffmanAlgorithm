#ifndef _HUFFMAN_TREE_NODES_HH_
#define _HUFFMAN_TREE_NODES_HH_

#include "HuffmanTreeExceptions.h"

/**
 * Node in the structure of the binary huffman tree
*/
class HuffmanTreeNode
{
public:
    virtual ~HuffmanTreeNode() = default;
    virtual bool isLeaf() const = 0;
    virtual const long &occuranceData() const = 0;
    virtual const char &characterData() const = 0;
    virtual HuffmanTreeNode *left() const = 0;
    virtual HuffmanTreeNode *right() const = 0;
    virtual int height() const = 0;
};

/**
 * Inner node of the binary huffman tree.
 * Invocation of the characterData() method results in HuffmanTreeExceptions::TreeNodeBadAccess()
*/
class HuffmanTreeInnerNode : public HuffmanTreeNode
{
private:
    long occurance_data;
    HuffmanTreeNode *_left;
    HuffmanTreeNode *_right;
    int _height;

public:
    HuffmanTreeInnerNode() = delete;
    HuffmanTreeInnerNode(HuffmanTreeNode *left, HuffmanTreeNode *right);
    ~HuffmanTreeInnerNode();

    bool isLeaf() const override;
    const long &occuranceData() const override;
    const char &characterData() const override;
    HuffmanTreeNode *left() const override;
    HuffmanTreeNode *right() const override;
    int height() const override;
};

/**
 * Leaf node of the binary huffman tree.
 * Invocation of the left() and right() method results in HuffmanTreeExceptions::TreeNodeBadAccess()
*/
class HuffmanTreeLeaf : public HuffmanTreeNode
{
private:
    long occurance_data;
    char character_data;

public:
    HuffmanTreeLeaf() = delete;
    HuffmanTreeLeaf(const long &occuranceData, char characterData);
    ~HuffmanTreeLeaf() = default;

    bool isLeaf() const override;
    const long &occuranceData() const override;
    const char &characterData() const override;
    HuffmanTreeNode *left() const override;
    HuffmanTreeNode *right() const override;
    int height() const override;
};

#endif
