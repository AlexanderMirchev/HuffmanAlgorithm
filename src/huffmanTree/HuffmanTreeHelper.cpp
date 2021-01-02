#include "HuffmanTreeHelper.h"

#include <algorithm>
#include <stdexcept>

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
                    // TODO make adequate
                    throw std::exception();
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
                throw std::exception();
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

std::multimap<int, char> HuffmanTreeHelper::sortDictionary(const std::unordered_map<char, int> &dictionary)
{
    std::multimap<int, char> result;
    std::transform(
        dictionary.begin(),
        dictionary.end(),
        std::inserter(result, result.begin()),
        [](std::pair<char, int> pair)
            -> std::pair<int, char> { return std::pair<int, char>(pair.second, pair.first); });

    return result;
}
