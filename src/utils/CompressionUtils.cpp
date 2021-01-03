#include "CompressionUtils.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>

#include "../huffmanTree/HuffmanTree.h"
#include "../huffmanTree/HuffmanTreeHelper.h"
#include "../huffmanTree/HuffmanTreeExceptions.h"
#include "BinaryUtils.h"

/**
 * Helper namespace
 */
namespace
{
    std::string deserializeDictionaryFromSource(std::ifstream &source)
    {
        std::stringstream dictionaryStream;

        std::string dictionaryLine;
        while (getline(source, dictionaryLine))
        {
            dictionaryStream << dictionaryLine << '\n';
        }

        return dictionaryStream.str();
    }
} // namespace

/**
 * Compression utilities implementations
 */
double CompressionUtils::compress(const std::string &sourceFilename, const std::string &destinationFilename)
{
    try
    {
        std::ifstream source(sourceFilename);

        if (!source.is_open())
        {
            throw CouldNotOpenFile(sourceFilename);
        }

        std::string input((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());

        std::unordered_map<char, int> dictionary = HuffmanTreeHelper::generateDictionaryFromText(input);
        HuffmanTree huffManTree = HuffmanTree(dictionary);

        std::ofstream destination(destinationFilename, std::ios::trunc);

        std::string convertedBinary = huffManTree.convertToBinary(input);

        destination << convertedBinary << std::endl;
        destination << HuffmanTreeHelper::serializeDictionary(dictionary);

        return (double) convertedBinary.size() / (8 * source.tellg());
    }
    catch (const BinaryUtils::BinaryConversionException &e)
    {
        char message[50];
        sprintf(message, "Invalid produced binary: %s", e.what());
        throw CompressionFailed(message);
    }
    catch (const HuffmanTreeExceptions::HuffmanTreeException &e)
    {
        throw CompressionFailed(e.what());
    }
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
    try
    {
        std::ifstream source(sourceFilename);

        if (!source.is_open())
        {
            throw CouldNotOpenFile(sourceFilename);
        }

        std::string input;
        std::getline(source, input);
        std::unordered_map<char, int> dictionary = HuffmanTreeHelper::deserializeDictionary(deserializeDictionaryFromSource(source));
        HuffmanTree huffManTree = HuffmanTree(dictionary);

        std::ofstream destination(destinationFilename);

        destination << huffManTree.convertFromBinary(input);
    }
    catch (const HuffmanTreeExceptions::HuffmanTreeException &e)
    {
        throw DecompressionFailed(e.what());
    }
}

void CompressionUtils::decompress(const std::string &sourceFilename)
{
    std::regex regexToExtractFilename("([[:w:]]+)\\.huf");
    std::smatch s;
    std::regex_search(sourceFilename, s, regexToExtractFilename);
    decompress(sourceFilename, s[1].str() + ".txt");
}
