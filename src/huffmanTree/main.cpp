#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include "../CompressionUtils.h"

int main()
{
    CompressionUtils::compress("kur2.txt", "kur");

    CompressionUtils::decompress("kur2.txt.huf", "qnko.txt");

    return 0;
}