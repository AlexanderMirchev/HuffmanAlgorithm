#include "CompressionController.h"

#include <iostream>

#include "CompressionUtils.h"

std::string CompressionController::runCommand(const std::string &command)
{
    // std::cout << commandMap.size();
    // for (auto commandPair : CompressionController::commandMap)
    // {
    //     std::cout << "kur" << std::endl;
    //     if (std::regex_match(command, commandPair.first))
    //     {
    //         std::cout << "kur" << std::endl;
    //         std::smatch s;
    //         std::regex_search(command, s, commandPair.first);

    //         // return commandPair.second(s);
    //     }
    // }

    return "No command matched.\n";
}

const CompressionController::IterableCommandMap CompressionController::commandMap{
    {compressionCommandRegex, compressionCallable},
    {decompressionCommandRegex, decompressionCallable},
};

const CompressionController::CommandCallable CompressionController::compressionCallable = [](const std::smatch s) -> std::string {
    // if (s[2].str().empty())
    // {
    //     return std::to_string(CompressionUtils::compress(s[1].str()));
    // }
    std::cout << s.size() << std::endl;
    return "";
    // return std::to_string(CompressionUtils::compress(s[1].str(), s[2].str()));
};
const CompressionController::CommandCallable CompressionController::decompressionCallable = [](const std::smatch s) -> std::string {
    // if (s.str(2).empty())
    // {
    //     CompressionUtils::decompress(s.str(1));
    //     return "Success";
    // }
    CompressionUtils::decompress(s.str(1), s.str(2));
    return "Success";
};

const std::regex CompressionController::compressionCommandRegex = std::regex("compress\\s-i\\s([[:w:]]+\\.txt)(?:\\s-o\\s([[:w:]]+\\.huf))?");

const std::regex CompressionController::decompressionCommandRegex = std::regex("decompress\\s-i\\s([[:w:]]+\\.huf)(?:\\s-o\\s([[:w:]]+\\.txt))?");