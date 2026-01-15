#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bitio.h"
#include "huffman.h"

static std::string formatBytes(uint64_t bytes) 
{
    const char* suffixes[] = { "B", "KB", "MB", "GB", "TB" };
    int i = 0;
    double count = bytes;

    while (count >= 1024 && i < 4) 
    {
        count /= 1024.0;
        i++;
    }
    double rounded = (int)(count * 10) / 10.0;

    return std::to_string(rounded) + " " + suffixes[i];
}


bool compressFile(const std::string &inPath, const std::string &outPath) {
    std::ifstream in(inPath, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open input file\n";
        return false;
    }

    // Count frequencies
    std::vector<uint64_t> freq(256, 0);
    uint64_t originalSize = 0;

    {
        char c;
        while (in.get(c)) {
            uint8_t b = static_cast<uint8_t>(c);
            freq[b]++;
            originalSize++;
        }
    }

    in.clear();
    in.seekg(0);

    Node *root = buildHuffmanTree(freq);
    std::string codes[256];
    if (root) buildCodes(root, "", codes);

    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open output file\n";
        freeTree(root);
        return false;
    }

    // Write header
    out.write("HUF1", 4);

    uint64_t sz = originalSize;
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));

    // write frequency table as uint32_t each (truncate if huge, but ok for normal files)
    for (int i = 0; i < 256; ++i) {
        uint32_t f = static_cast<uint32_t>(freq[i]);
        out.write(reinterpret_cast<const char*>(&f), sizeof(f));
    }

    BitWriter bw(out);

    // Encode data
    char c;
    while (in.get(c)) {
        uint8_t b = static_cast<uint8_t>(c);
        const std::string &code = codes[b];
        bw.writeBits(code);
    }
    bw.flush();

    freeTree(root);
    out.close();

    // Get compressed file size
    uint64_t compressedSize;
    struct stat st;
    if (stat(outPath.c_str(), &st) == 0) {
        compressedSize = st.st_size;
    } else {
        std::cerr << "Warning: cannot get compressed file size\n";
    }

    // Print stats
    std::cerr << "Original size  : " << formatBytes(originalSize) << " (" << originalSize << " bytes)\n";
    std::cerr << "Compressed size: " << formatBytes(compressedSize) << " (" << compressedSize << " bytes)\n";

    if (originalSize == 0) {
        std::cerr << "Compression ratio: N/A (empty input)\n";
    } else {
        double ratio = 100.0 * static_cast<double>(compressedSize) / static_cast<double>(originalSize);
        double reduction = 100.0 - ratio;
        std::cerr << std::fixed << std::setprecision(2);
        std::cerr << "Compression ratio: " << ratio << "% (size is " << reduction << "% smaller)\n";
    }
    return true;
}
