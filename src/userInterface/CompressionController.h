#ifndef _COMPRESSION_CONTROLLER_HH_
#define _COMPRESSION_CONTROLLER_HH_

#include <functional>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "UseCase.h"

class CompressionController
{
public:
    static void start();
private:
    static std::string runCommand(const std::string &command);

    using UseCaseGenerator = std::function<std::unique_ptr<UseCase>(const std::smatch &)>;
    using IterableRegexUseCaseMap = std::vector<std::pair<std::regex, UseCaseGenerator>>;

    static const std::regex COMPRESSION_REGEX;
    static const std::regex COMPRESSION_DBG_REGEX;
    static const std::regex DECOMPRESSION_REGEX;

    static const IterableRegexUseCaseMap REGEX_USE_CASE_MAP;

    static const std::string NO_MATCH_MESSAGE;
};

#endif
