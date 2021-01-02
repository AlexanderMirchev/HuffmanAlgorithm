#include "HuffmanTreeHelper.h"

#include <algorithm>
#include <stdexcept>

#include "HuffmanTreeExceptions.h"

std::string HuffmanTreeHelper::serializeDictionary(const std::unordered_map<char, int> &dictionary)
{
    std::string result;

    for (auto pair : dictionary)
    {
        result.push_back(pair.first);
        result.append(std::to_string(pair.second));
        result.push_back('|');
    }

    return result;
}

std::unordered_map<char, int> HuffmanTreeHelper::deserializeDictionary(const std::string &serialized)
{
    std::unordered_map<char, int> resultDictionary;

    char currentCharacter = '|';
    std::string currentOccurances;

    for (auto symbol : serialized)
    {
        if (currentCharacter == '|')
        {
            currentCharacter = symbol;
        }
        else
        {
            if (symbol == '|')
            {
                if (currentOccurances.empty())
                {
                    throw HuffmanTreeExceptions::BadSerializedDictionary();
                }
                else
                {
                    resultDictionary[currentCharacter] = std::stoi(currentOccurances);
                    currentCharacter = '|';
                    currentOccurances.clear();
                }
            }

            else if (symbol >= '0' && symbol <= '9')
            {
                currentOccurances.push_back(symbol);
            }

            else
            {
                throw HuffmanTreeExceptions::BadSerializedDictionary();
            }
        }
    }

    return resultDictionary;
}

std::unordered_map<char, int> HuffmanTreeHelper::generateDictionaryFromText(const std::string &text)
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
    return dictionary;
}
