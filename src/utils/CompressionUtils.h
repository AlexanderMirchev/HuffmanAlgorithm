#ifndef _COMPRESSION_UTILS_HH_
#define _COMPRESSION_UTILS_HH_

#include <cstring>
#include <string>

namespace CompressionUtils
{
    /**
     * Generates new text file with .huf extension that contains the compressed data from the file with <source>.txt.
     * If no different name is selected the new file wil have the same name as the old with .huf extension.
     * 
     * Returns compression ratio
    */
    double compress(const std::string &source, const std::string &destination);
    double compress(const std::string &source);

    /**
     * Generates new .txt file that contains the decompressed data from the file with <source>.huf.
     * If no different name is selected the new file wil have the same name as the old with .txt extension.
    */
    void decompress(const std::string &source, const std::string &destination);
    void decompress(const std::string &source);

    struct CompressionException : public std::exception
    {
        virtual ~CompressionException() = default;
        virtual const char *what() const noexcept = 0;
    };

    class CouldNotOpenFile : public CompressionException
    {
    private:
        char message[80];

    public:
        CouldNotOpenFile() = delete;
        ~CouldNotOpenFile() = default;
        CouldNotOpenFile(const std::string &filename)
        {
            sprintf(message, "Could not open file %s.", filename.c_str());
        }
        const char *what() const noexcept override
        {
            return message;
        }
    };

    class CompressionFailed : public CompressionException
    {
    private:
        char message[100];

    public:
        CompressionFailed() = delete;
        ~CompressionFailed() = default;
        CompressionFailed(const std::string &reason)
        {
            sprintf(message, "Compression failed. Reason: %s", reason.c_str());
        }
        const char *what() const noexcept override
        {
            return message;
        }
    };

    class DecompressionFailed : public CompressionException
    {
    private:
        char message[100];

    public:
        DecompressionFailed() = delete;
        ~DecompressionFailed() = default;
        DecompressionFailed(const std::string &reason)
        {
            sprintf(message, "Decompression failed. Reason: %s", reason.c_str());
        }
        const char *what() const noexcept override
        {
            return message;
        }
    };

} // namespace CompressionUtils

#endif
