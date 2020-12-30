#ifndef _COMPRESSION_UTILS_HH_
#define _COMPRESSION_UTILS_HH_

#include <string>

namespace CompressionUtils
{
    /**
     * Generates new text file with .huf extension that contains the compressed data from the file with filename.
     * If no different name is selected the new file wil have the same name as the old with .huf extension.
     * 
     * Returns compression ratio
    */
    double compress(const std::string &filename, const std::string &newFileName);
    // void compress(const std::string& filename);

    /**
     * Generates new text file that contains the decompressed data from the .huf file with filename.
     * If no different name is selected the new file wil have the same name as the old with .txt extension.
    */
    void decompress(const std::string &filename, const std::string &newFileName);
    // void decompress(const std::string& filename);

    int transformBinaryString(const std::string &);
} // namespace CompressionUtils
#endif