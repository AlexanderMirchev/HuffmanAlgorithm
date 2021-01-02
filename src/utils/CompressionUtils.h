#ifndef _COMPRESSION_UTILS_HH_
#define _COMPRESSION_UTILS_HH_

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
} // namespace CompressionUtils
#endif
