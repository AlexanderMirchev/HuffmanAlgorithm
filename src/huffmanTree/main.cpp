#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"

int main()
{
    std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    auto dictionary = HuffmanTreeHelper::generateDictionaryFromText(text);

    std::cout << "Unsorted dictionary" << std::endl;
    for (auto pair : dictionary)
    {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "Sorted dictionary" << std::endl;
    auto sortedDictionary = HuffmanTreeHelper::sortDictionary(dictionary);
    for (auto pair : sortedDictionary)
    {
        std::cout << pair.second << " " << pair.first << std::endl;
    }

    std::string serDic = HuffmanTreeHelper::serializeDictionary(sortedDictionary);

    auto deserDic = HuffmanTreeHelper::deserializeDictionary(serDic);
    for (auto pair : deserDic)
    {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    // HuffmanTree huffmanTree = HuffmanTree(HuffmanTreeHelper::generateDictionaryFromText(text));

    // std::string binary = huffmanTree.convertToBinary(text);
    // std::cout << binary << std::endl;

    // std::cout << huffmanTree.convertFromBinary(binary) << std::endl;

    return 0;
}