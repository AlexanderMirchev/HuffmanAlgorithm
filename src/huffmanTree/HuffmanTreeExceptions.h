#ifndef _HUFFMAN_TREE_EXCEPTIONS_HH_
#define _HUFFMAN_TREE_EXCEPTIONS_HH_

#include <stdexcept>

namespace HuffmanTreeExceptions
{
    struct HuffmanTreeException : public std::exception
    {
        virtual ~HuffmanTreeException() = default;
        virtual const char *what() const noexcept = 0;
    };

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