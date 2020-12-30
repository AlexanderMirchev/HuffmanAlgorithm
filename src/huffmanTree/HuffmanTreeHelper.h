#ifndef _HUFFMAN_TREE_HELPER_HH_
#define _HUFFMAN_TREE_HELPER_HH_

#include <unordered_map>
#include <map>
#include <string>

namespace HuffmanTreeHelper
{
    std::string serializeDictionary(const std::unordered_map<char, int> &);

    std::unordered_map<char, int> deserializeDictionary(const std::string &);

    std::unordered_map<char, int> generateDictionaryFromText(const std::string &);

    std::multimap<int, char> sortDictionary(const std::unordered_map<char, int> &);

} // namespace HuffmanTreeHelper

#endif
