#ifndef _BINARY_UTILS_HH_
#define _BINARY_UTILS_HH_

#include <string>

namespace BinaryUtils
{
    /**
     * Converts int to binary, fullByte converts it to 8 digit string
    */
    std::string intToBinary(const int &);
    std::string intToBinary(const int &, const bool& fullByte);

    int binaryToInt(const std::string &);

    struct BinaryConversionException : public std::exception
    {
        const char *what() const noexcept override
        {
            return "Error in converting binary expression: contains character other than 0 and 1.";
        }
    };
} // namespace BinaryUtils

#endif
