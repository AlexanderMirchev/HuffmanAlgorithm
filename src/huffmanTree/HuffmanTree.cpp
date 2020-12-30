#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <queue>
#include <functional>

HuffmanTree::HuffmanTree(const std::unordered_map<char, int> &dictionary) : root{nullptr}
{
    // TODO make less cancer if possible
    struct NodeWrapper
    {
        HuffmanTreeNode *node;
        int order;
    };

    auto nodeWrapperComparator = [](NodeWrapper m, NodeWrapper n) -> bool {
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
    std::priority_queue<
        NodeWrapper,
        std::vector<NodeWrapper>,
        std::function<bool(NodeWrapper, NodeWrapper)>>
        priorityNodes(nodeWrapperComparator);

    for (auto pair : dictionary)
    {
        priorityNodes.push({new HuffmanTreeLeaf(pair.second, pair.first), 0});
    }

    int order = 1;
    while (priorityNodes.size() >= 2)
    {
        HuffmanTreeNode *left = priorityNodes.top().node;
        priorityNodes.pop();

        HuffmanTreeNode *right = priorityNodes.top().node;
        priorityNodes.pop();

        priorityNodes.push({new HuffmanTreeInnerNode(left, right), order++});
    }

    root = priorityNodes.top().node;
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
        if (searchingNode->isLeaf())
        {
            result.push_back(searchingNode->characterData());
            searchingNode = root;
        }

        if (elem == '0')
        {
            searchingNode = searchingNode->left();
        }
        else if (elem == '1')
        {
            searchingNode = searchingNode->right();
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
