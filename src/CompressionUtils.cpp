#include "CompressionUtils.h"

#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "huffmanTree/HuffmanTree.h"
#include "huffmanTree/HuffmanTreeHelper.h"

double CompressionUtils::compress(const std::string &filename, const std::string &newFileName)
{
    std::ifstream fileToCompress(filename);
    std::string textToCompress((std::istreambuf_iterator<char>(fileToCompress)),
                               std::istreambuf_iterator<char>());

    std::unordered_map<char, int> dictionary = HuffmanTreeHelper::generateDictionaryFromText(textToCompress);
    HuffmanTree huffManTree = HuffmanTree(dictionary);

    // TODO check if has .huf
    std::ofstream destination(filename + ".huf", std::ios::trunc);

    int memoryCounter = 0;
    std::string tempBinary;
    for (auto symbol : huffManTree.convertToBinary(textToCompress))
    {
        if (tempBinary.size() == 8)
        {

            destination << std::bitset<8>(tempBinary).to_ulong() << ' ';
            memoryCounter++;
            tempBinary.clear();
        }
        tempBinary.push_back(symbol);
    }
    if (!tempBinary.empty())
    {
        destination << std::bitset<8>(tempBinary).to_ulong();
        memoryCounter++;
    }
    destination << std::endl;
    destination << HuffmanTreeHelper::serializeDictionary(dictionary);

    return (double)memoryCounter / fileToCompress.tellg();
}

int CompressionUtils::transformBinaryString(const std::string &binary)
{
    int result = 0;
    int power = 0;
    for (std::string::const_reverse_iterator rit = binary.rbegin(); rit != binary.rend(); ++rit)
    {
        char current = *rit;

        if (current == '1')
        {
            result += std::pow(2, power);
            power++;
        }
        else if (current == '0')
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

std::string toBinary(int n);
void CompressionUtils::decompress(const std::string &filename, const std::string &newFileName)
{
    std::ifstream source(filename);

    std::string encrypted;
    std::getline(source, encrypted);

    std::string binaryEncrypted;
    std::string tempNumber;
    for (auto symbol : encrypted)
    {
        if (symbol <= '9' && symbol >= '0')
        {
            tempNumber += symbol;
        }
        else if (symbol == ' ')
        {
            binaryEncrypted.append(std::bitset<8>(std::stoi(tempNumber)).to_string());
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
        binaryEncrypted.append(toBinary(std::stoi(tempNumber)));
    }

    std::stringstream dictionaryStream;

    if (source.is_open())
    {
        std::string dictionaryLine;
        while (getline(source, dictionaryLine))
        {
            dictionaryStream << dictionaryLine << '\n';
        }
    }

    HuffmanTree huffManTree = HuffmanTree(HuffmanTreeHelper::deserializeDictionary(dictionaryStream.str()));

    std::ofstream destination(newFileName);

    destination << huffManTree.convertFromBinary(binaryEncrypted);
}

std::string toBinary(int n)
{
    std::string r;
    if (n == 0)
    {
        return "0";
    }
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}