#include "CompressionUtils.h"

#include <cmath>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

#include "../huffmanTree/HuffmanTree.h"
#include "../huffmanTree/HuffmanTreeHelper.h"
#include "BinaryUtils.h"

/**
 * Helper namespace
 */
namespace
{
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
} // namespace

/**
 * Compression utilities implementations
 */
double CompressionUtils::compress(const std::string &sourceFilename, const std::string &destinationFilename)
{
    std::ifstream source(sourceFilename);
    std::string input((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());

    std::unordered_map<char, int> dictionary = HuffmanTreeHelper::generateDictionaryFromText(input);
    HuffmanTree huffManTree = HuffmanTree(dictionary);

    std::ofstream destination(destinationFilename, std::ios::trunc);

    int compressedMemory = compressAndSerializeText(huffManTree.convertToBinary(input), destination);

    destination << HuffmanTreeHelper::serializeDictionary(dictionary);

    return (double)compressedMemory / source.tellg();
}

double CompressionUtils::compress(const std::string &sourceFilename)
{
    std::regex regexToExtractFilename("([[:w:]]+)\\.txt");
    std::smatch s;
    std::regex_search(sourceFilename, s, regexToExtractFilename);
    return compress(sourceFilename, s[1].str() + ".huf");
}

void CompressionUtils::decompress(const std::string &sourceFilename, const std::string &destinationFilename)
{
    std::ifstream source(sourceFilename);

    std::string input;
    std::getline(source, input);

    HuffmanTree huffManTree = HuffmanTree(HuffmanTreeHelper::deserializeDictionary(deserializeDictionaryFromSource(source)));

    std::ofstream destination(destinationFilename);

    destination << huffManTree.convertFromBinary(decompressSerializedText(input));
}

void CompressionUtils::decompress(const std::string &sourceFilename)
{
    std::regex regexToExtractFilename("([[:w:]]+\\.huf");
    std::smatch s;
    std::regex_search(sourceFilename, s, regexToExtractFilename);
    decompress(sourceFilename, s[1].str() + ".txt");
}
