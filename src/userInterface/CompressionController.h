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
    // CompressionController();
    // ~CompressionController();

    static std::string runCommand(const std::string &command);

private:
    using UseCaseGenerator = std::function<std::unique_ptr<UseCase>(const std::smatch&)>;
    using IterableCommandMap = std::vector<std::pair<std::regex, UseCaseGenerator>>;

    static const std::regex compressionCommandRegex;
    static const std::regex decompressionCommandRegex;

    static const IterableCommandMap commandMap;

    // TODO implement properly
    // template<class T>
    // static std::string execute(std::function<T(std::string)>);
};

#endif