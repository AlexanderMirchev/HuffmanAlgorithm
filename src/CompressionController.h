#ifndef _COMPRESSION_CONTROLLER_HH_
#define _COMPRESSION_CONTROLLER_HH_

#include <string>

class CompressionController
{
public:
    CompressionController();
    ~CompressionController();

    std::string runCommand(const std::string& command) const;
};

#endif