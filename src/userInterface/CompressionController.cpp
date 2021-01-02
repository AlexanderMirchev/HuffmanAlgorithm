#include "CompressionController.h"

#include <iostream>

void CompressionController::start()
{
    bool shouldContinue = true;
    do
    {
        std::string line;
        std::cout << "~ ";
        std::getline(std::cin, line);

        if (line == "close")
        {
            shouldContinue = false;
        }
        else
        {
            std::cout << runCommand(line) << std::endl;
        }

    } while (shouldContinue);
}

std::string CompressionController::runCommand(const std::string &command)
{
    for (auto commandPair : CompressionController::REGEX_USE_CASE_MAP)
    {
        if (std::regex_match(command, commandPair.first))
        {
            std::smatch s;
            std::regex_search(command, s, commandPair.first);

            return commandPair.second(s)->operator()();
        }
    }

    return NO_MATCH_MESSAGE;
}

const std::regex CompressionController::COMPRESSION_REGEX = std::regex("compress\\s-i\\s([[:w:]]+\\.txt)(?:\\s-o\\s([[:w:]]+\\.huf))?");

const std::regex CompressionController::DECOMPRESSION_REGEX = std::regex("decompress\\s-i\\s([[:w:]]+\\.huf)(?:\\s-o\\s([[:w:]]+\\.txt))?");

const CompressionController::IterableRegexUseCaseMap CompressionController::REGEX_USE_CASE_MAP{
    {COMPRESSION_REGEX, [](const std::smatch &s) { return std::unique_ptr<UseCase>(new CompressionUseCase(s[1], s[2])); }},
    {DECOMPRESSION_REGEX, [](const std::smatch &s) { return std::unique_ptr<UseCase>(new DecompressionUseCase(s[1], s[2])); }},
};

const std::string CompressionController::NO_MATCH_MESSAGE = std::string("No command matched.\nList of possible commands:\n"
                                                 "compress -i <source>.txt (-o<destination>.huf)[optional] - compress file from .txt to .huf\n"
                                                 "decompress -i <source>.huf (-o<destination>.txt)[optional] - decompress file from .huf to .txt\n"
                                                 "close - close the program");
