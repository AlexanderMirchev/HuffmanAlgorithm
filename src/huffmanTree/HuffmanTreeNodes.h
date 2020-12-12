
#ifndef _HUFFMAN_TREE_NODES_HH_
#define _HUFFMAN_TREE_NODES_HH_

#include <iostream>

class HuffmanTreeNode
{
public:
    virtual ~HuffmanTreeNode() = default;
    virtual bool isLeaf() const = 0;
    virtual const long &occuranceData() const = 0;
    virtual const char &characterData() const = 0;
    virtual HuffmanTreeNode *left() const = 0;
    virtual HuffmanTreeNode *right() const = 0;
};

class HuffmanTreeInnerNode : public HuffmanTreeNode
{
private:
    long occurance_data;
    HuffmanTreeNode *_left;
    HuffmanTreeNode *_right;

public:
    HuffmanTreeInnerNode() = delete;
    HuffmanTreeInnerNode(const long &occuranceData, HuffmanTreeNode *left, HuffmanTreeNode *right);
    ~HuffmanTreeInnerNode();

    bool isLeaf() const override;
    const long &occuranceData() const override;
    const char &characterData() const override;
    HuffmanTreeNode *left() const override;
    HuffmanTreeNode *right() const override;
};

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
};

namespace HuffmanTreeNodeExceptions
{
    // TODO implement adequate exceptions for all cases

}; // namespace HuffmanTreeNodeExceptions

#endif
