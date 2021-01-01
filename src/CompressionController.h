#ifndef _COMPRESSION_CONTROLLER_HH_
#define _COMPRESSION_CONTROLLER_HH_

#include <functional>
#include <regex>
#include <string>
#include <vector>

class CompressionController
{
public:
    // CompressionController();
    // ~CompressionController();

    static std::string runCommand(const std::string &command);

private:
    using CommandCallable = std::function<std::string(const std::smatch)>;
    using IterableCommandMap = std::vector<std::pair<std::regex, CommandCallable>>;

    static const std::regex compressionCommandRegex;
    static const std::regex decompressionCommandRegex;

    static const CommandCallable compressionCallable;
    static const CommandCallable decompressionCallable;
    
    static const IterableCommandMap commandMap;

    // TODO implement properly
    // template<class T>
    // static std::string execute(std::function<T(std::string)>);
};

#endif