#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanTreeHelper.h"
#include "../CompressionUtils.h"
#include "../userInterface/CompressionController.h"

int main()
{
    // std::cout << CompressionController::runCommand("compress -i kur.txt -o kur.huf") << std::endl;
    
    std::cout << CompressionController::runCommand("compress -i kur.txt") << std::endl;

    return 0;
}