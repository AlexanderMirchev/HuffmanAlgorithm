#include "UseCase.h"

#include <iomanip>
#include <sstream>

#include "../utils/CompressionUtils.h"

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
    catch (const CompressionUtils::CompressionException &e)
    {
        return e.what();
    }
    catch (const std::exception &e)
    {
        return "Compression failed with unhandled error";
    }
}

std::string CompressionUseCase::getPercentage(const double &n) const
{
    std::stringstream percentageStream;
    percentageStream << std::fixed << std::setprecision(2) << n * 100 << "%";
    return percentageStream.str();
}

CompressionDbgUseCase::CompressionDbgUseCase(const std::string &source, const std::string &destination) : CompressionUseCase(source, destination) {}

std::string CompressionDbgUseCase::operator()() const
{
    try
    {
        std::pair<double, std::string> result;
        if (this->destination.empty())
        {
            result = CompressionUtils::compressDbg(this->source);
        }
        else
        {
            result = CompressionUtils::compressDbg(this->source, this->destination);
        }

        return "Compression successful with compression rate of " + getPercentage(result.first) + "\nDebug info:\n" + result.second;
    }
    catch (const CompressionUtils::CompressionException &e)
    {
        return e.what();
    }
    catch (const std::exception &e)
    {
        return "Compression failed with unhandled error";
    }
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
    catch (const CompressionUtils::CompressionException &e)
    {
        return e.what();
    }
    catch (const std::exception &e)
    {
        return "Decompression failed with unhandled error";
    }
}
