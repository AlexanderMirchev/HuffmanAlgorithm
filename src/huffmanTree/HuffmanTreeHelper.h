#ifndef _HUFFMAN_TREE_HELPER_HH_
#define _HUFFMAN_TREE_HELPER_HH_

#include <unordered_map>
#include <string>

/**
 * Namespace with helper methods that create and transform dictionaries that are used together with the huffmantree.
 * Dictionary is an unordered map with char->int pairs illustrating the occurance data of each character
*/
namespace HuffmanTreeHelper
{
    /**
     * Serializes dictionary with given pattern <char><number>| pattern
    */
    std::string serializeDictionary(const std::unordered_map<char, int> &);

    /**
     * Desereializes dictionary from source with pattern <char><number>| pattern
     * 
     * @throws HuffmanTreeExceptions::BadSerializedDictionary 
    */
    std::unordered_map<char, int> deserializeDictionary(const std::string &);

    /**
     * Creates dictionary from string
    */
    std::unordered_map<char, int> generateDictionaryFromText(const std::string &);
} // namespace HuffmanTreeHelper

#endif
