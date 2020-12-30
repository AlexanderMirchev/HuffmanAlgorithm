#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include "../CompressionUtils.h"

int main()
{
    // std::string text = "kurak";
    // auto dictionary = HuffmanTreeHelper::generateDictionaryFromText(text);

    // std::cout << "Unsorted dictionary" << std::endl;
    // for (auto pair : dictionary)
    // {
    //     std::cout << pair.first << " " << pair.second << std::endl;
    // }

    // std::cout << "Sorted dictionary" << std::endl;
    // auto sortedDictionary = HuffmanTreeHelper::sortDictionary(dictionary);
    // for (auto pair : sortedDictionary)
    // {
    //     std::cout << pair.second << " " << pair.first << std::endl;
    // }

    // std::string serDic = HuffmanTreeHelper::serializeDictionary(sortedDictionary);

    // auto deserDic = HuffmanTreeHelper::deserializeDictionary(serDic);
    // for (auto pair : deserDic)
    // {
    //     std::cout << pair.first << " " << pair.second << std::endl;
    // }

    // HuffmanTree huffmanTree = HuffmanTree(HuffmanTreeHelper::generateDictionaryFromText(text));

    // std::string binary = huffmanTree.convertToBinary(text);
    // std::cout << binary << std::endl;

    // std::cout << huffmanTree.convertFromBinary(binary) << std::endl;

    CompressionUtils::compress("kur2.txt", "kur");

    CompressionUtils::decompress("kur2.txt.huf", "qnko.txt");

    return 0;
}