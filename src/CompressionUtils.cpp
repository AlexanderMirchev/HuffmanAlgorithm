#include "CompressionUtils.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "huffmanTree/HuffmanTree.h"
#include "huffmanTree/HuffmanTreeHelper.h"
#include "utils/BinaryUtils.h"

int compressAndSerializeText(const std::string &binary, std::ofstream &destination);

double CompressionUtils::compress(const std::string &filename, const std::string &newFileName)
{
    std::ifstream fileToCompress(filename);
    std::string textToCompress((std::istreambuf_iterator<char>(fileToCompress)),
                               std::istreambuf_iterator<char>());

    std::unordered_map<char, int> dictionary = HuffmanTreeHelper::generateDictionaryFromText(textToCompress);
    HuffmanTree huffManTree = HuffmanTree(dictionary);

    std::ofstream destination(filename + ".huf", std::ios::trunc);

    int compressedMemory = compressAndSerializeText(huffManTree.convertToBinary(textToCompress), destination);

    destination << HuffmanTreeHelper::serializeDictionary(dictionary);

    return (double)compressedMemory / fileToCompress.tellg();
}

std::string decompressSerializedText(const std::string &compressed);

std::string deserializeDictionaryFromSource(std::ifstream &source);

void CompressionUtils::decompress(const std::string &filename, const std::string &newFileName)
{
    std::ifstream source(filename);

    std::string compressedInput;
    std::getline(source, compressedInput);

    HuffmanTree huffManTree = HuffmanTree(HuffmanTreeHelper::deserializeDictionary(deserializeDictionaryFromSource(source)));

    std::ofstream destination(newFileName);

    destination << huffManTree.convertFromBinary(decompressSerializedText(compressedInput));
}

int compressAndSerializeText(const std::string &binary, std::ofstream &destination)
{
    int compressedMemory = 0;

    std::string tempBinary;
    for (auto symbol : binary)
    {
        if (tempBinary.size() == 8)
        {
            destination << BinaryUtils::binaryToInt(tempBinary) << ' ';
            compressedMemory++;
            tempBinary.clear();
        }
        tempBinary.push_back(symbol);
    }
    if (!tempBinary.empty())
    {
        destination << BinaryUtils::binaryToInt(tempBinary);
        compressedMemory++;
    }

    destination << std::endl;

    return compressedMemory;
}

std::string decompressSerializedText(const std::string &compressed)
{
    std::string decompressedBinary;
    std::string tempNumber;

    for (auto symbol : compressed)
    {
        if (symbol <= '9' && symbol >= '0')
        {
            tempNumber += symbol;
        }
        else if (symbol == ' ')
        {
            decompressedBinary.append(BinaryUtils::intToBinary(std::stoi(tempNumber), true));
            tempNumber.clear();
        }
        else
        {
            // TODO adequate
            throw std::exception();
        }
    }
    if (!tempNumber.empty())
    {
        decompressedBinary.append(BinaryUtils::intToBinary(std::stoi(tempNumber)));
    }
    
    return decompressedBinary;
}

std::string deserializeDictionaryFromSource(std::ifstream &source)
{
    std::stringstream dictionaryStream;

    if (source.is_open())
    {
        std::string dictionaryLine;
        while (getline(source, dictionaryLine))
        {
            dictionaryStream << dictionaryLine << '\n';
        }
    }

    return dictionaryStream.str();
}
