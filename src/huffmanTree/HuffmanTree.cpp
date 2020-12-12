#include "HuffmanTree.h"
#include <stdexcept>
#include <queue>
#include <algorithm>

HuffmanTree::HuffmanTree(const std::string &text) : root{nullptr}
{
    const std::multimap<int, char> sortedDictionary = sortedDictionaryOfSymbolsInText(text);

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
        std::cout << root->occuranceData() << std::endl;
    }
}
HuffmanTree::~HuffmanTree()
{
    delete root;
}

std::multimap<int, char> HuffmanTree::sortedDictionaryOfSymbolsInText(const std::string &text)
{
    std::unordered_map<char, int> dictionary;

    for (auto symbol : text)
    {
        try
        {
            int &occurances = dictionary.at(symbol);
            occurances++;
        }
        catch (const std::out_of_range &e)
        {
            dictionary[symbol] = 1;
        }
    }

    std::multimap<int, char> result;
    std::transform(
        dictionary.begin(),
        dictionary.end(),
        std::inserter(result, result.begin()),
        [](std::pair<char, int> pair)
            -> std::pair<int, char> { return std::pair<int, char>(pair.second, pair.first); });

    return result;
}
