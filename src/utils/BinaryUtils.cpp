#include "BinaryUtils.h"

#include <cmath>

std::string BinaryUtils::intToBinary(const int &number)
{
    return intToBinary(number, false);
}

std::string BinaryUtils::intToBinary(const int &number, const bool &fullByte)
{
    std::string binary;
    if (number == 0)
    {
        binary = "0";
    }

    int n = number;
    while (n != 0)
    {
        binary = (n % 2 == 0 ? "0" : "1") + binary;
        n /= 2;
    }

    if (fullByte)
    {
        while (binary.size() != 8)
        {
            binary = "0" + binary;
        }
    }

    return binary;
}

int BinaryUtils::binaryToInt(const std::string &binary)
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
            throw BinaryConversionException();
        }
    }

    return result;
}
