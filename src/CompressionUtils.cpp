#include "CompressionUtils.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "huffmanTree/HuffmanTree.h"
#include "huffmanTree/HuffmanTreeHelper.h"

void CompressionUtils::compress(const std::string &filename, const std::string &newFileName)
{
    std::ifstream fileToCompress(filename);
    std::string textToCompress((std::istreambuf_iterator<char>(fileToCompress)),
                               std::istreambuf_iterator<char>());

    std::unordered_map<char, int> dictionary = HuffmanTreeHelper::generateDictionaryFromText(textToCompress);
    HuffmanTree huffManTree = HuffmanTree(dictionary);

    // TODO check if has .huf
    std::ofstream destination(filename + ".huf", std::ios::trunc);
    destination << HuffmanTreeHelper::serializeDictionary(dictionary);
    destination << std::endl;

    std::string tempBinary;
    for (auto symbol : huffManTree.convertToBinary(textToCompress))
    {
        if (tempBinary.size() == 8)
        {
            destination << CompressionUtils::transformBinaryString(tempBinary) << ' ';
            tempBinary.clear();
        }
        else
        {
            tempBinary.push_back(symbol);
        }
    }
    if (!tempBinary.empty())
    {
        destination << CompressionUtils::transformBinaryString(tempBinary);
    }
}

int CompressionUtils::transformBinaryString(const std::string &binary)
{
    int result = 0;
    int power = 0;
    for(std::string::const_reverse_iterator rit = binary.rbegin(); rit != binary.rend();++rit)
    {
        char current = *rit;

        if(current == '1')
        {
            result += std::pow(2, power);
            power++;
        }
        else if(current == '0')
        {
            power++;
        }
        else
        {
            throw std::exception();
        }
    }

    return result;
}