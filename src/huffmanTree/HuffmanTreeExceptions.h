#ifndef _HUFFMAN_TREE_EXCEPTIONS_HH_
#define _HUFFMAN_TREE_EXCEPTIONS_HH_

#include <stdexcept>

/**
 * Exceptions that may occur in the inner usage of huffman tree algorithm
*/
namespace HuffmanTreeExceptions
{
    /**
     * Base expcetion
    */
    struct HuffmanTreeException : public std::exception
    {
        virtual ~HuffmanTreeException() = default;
        virtual const char *what() const noexcept = 0;
    };

    /**
     * Exception thrown when serialized input contains elements other than 0 and 1
    */
    class BadSerializedInput : public HuffmanTreeException
    {
    public:
        BadSerializedInput() = default;
        ~BadSerializedInput() = default;
        const char *what() const noexcept override
        {
            return "Input you are trying to decompress contains characters other than 0 and 1 digits";
        }
    };

    /**
     * Exception thrown when serialized dictionary doesn't match the dictionary pattern
    */
    class BadSerializedDictionary : public HuffmanTreeException
    {
    public:
        BadSerializedDictionary() = default;
        ~BadSerializedDictionary() = default;
        const char *what() const noexcept override
        {
            return "Dictionary you are trying to decompress doesn't match <char><number>| pattern";
        }
    };

    /**
     * Exception thrown when a node gets called a function not mathcing its polymorphic type
    */
    class TreeNodeBadAccess : public HuffmanTreeException
    {
    public:
        TreeNodeBadAccess() = default;
        ~TreeNodeBadAccess() = default;
        const char *what() const noexcept override
        {
            return "Compression tree node occurred bad access";
        }
    };

} // namespace HuffmanTreeExceptions
#endif