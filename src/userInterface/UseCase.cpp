#include "UseCase.h"

#include <iomanip>
#include <sstream>

#include "../CompressionUtils.h"

CompressionUseCase::CompressionUseCase(const std::string &source, const std::string &destination)
{
    this->source = source;
    this->destination = destination;
}

std::string CompressionUseCase::operator()() const
{
    try
    {
        double result;
        if (this->destination.empty())
        {
            result = CompressionUtils::compress(this->source);
        }
        else
        {
            result = CompressionUtils::compress(this->source, this->destination);
        }

        return "Compression successful with compression rate of " + getPercentage(result);
    }
    catch (const std::exception &e)
    {
        // TODO adequately
        return "Could not complete operation. Reason: " + std::string(e.what());
    }
}

std::string CompressionUseCase::getPercentage(const double &n) const
{
    std::stringstream percentageStream;
    percentageStream << std::fixed << std::setprecision(2) << n * 100 << "%";
    return percentageStream.str();
}

DecompressionUseCase::DecompressionUseCase(const std::string &source, const std::string &destination)
{
    this->source = source;
    this->destination = destination;
}

std::string DecompressionUseCase::operator()() const
{
    try
    {
        if (this->destination.empty())
        {
            CompressionUtils::decompress(this->source);
        }
        else
        {
            CompressionUtils::decompress(this->source, this->destination);
        }
        return "Decompression successful";
    }
    catch (const std::exception &e)
    {
        // TODO adequately
        return "Could not complete operation. Reason: " + std::string(e.what());
    }
}
