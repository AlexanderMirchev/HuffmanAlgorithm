#include "CompressionController.h"

#include <iostream>

std::string CompressionController::runCommand(const std::string &command)
{
    // std::cout << commandMap.size();
    for (auto commandPair : CompressionController::commandMap)
    {
        // std::cout << "kur" << std::endl;
        if (std::regex_match(command, commandPair.first))
        {
            // std::cout << "kur" << std::endl;
            std::smatch s;
            std::regex_search(command, s, commandPair.first);

            return commandPair.second(s)->operator()();
        }
    }

    return "No command matched.\n";
}

const std::regex CompressionController::compressionCommandRegex = std::regex("compress\\s-i\\s([[:w:]]+\\.txt)(?:\\s-o\\s([[:w:]]+\\.huf))?");

const std::regex CompressionController::decompressionCommandRegex = std::regex("decompress\\s-i\\s([[:w:]]+\\.huf)(?:\\s-o\\s([[:w:]]+\\.txt))?");

const CompressionController::IterableCommandMap CompressionController::commandMap{
    {compressionCommandRegex, [](const std::smatch &s) { return std::unique_ptr<UseCase>(new CompressionUseCase(s[1], s[2])); }},
    {decompressionCommandRegex, [](const std::smatch &s) { return std::unique_ptr<UseCase>(new DecompressionUseCase(s[1], s[2])); }},
};