#include <iostream>
#include <fstream>
#include <vector>
#include "bitio.h"
#include "huffman.h"

bool decompressFile(const std::string &inPath, const std::string &outPath) {
    std::ifstream in(inPath, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open input file\n";
        return false;
    }

    char magic[4];
    in.read(magic, 4);
    if (in.gcount() != 4 || std::string(magic, 4) != "HUF1") {
        std::cerr << "Not a valid HUF1 file\n";
        return false;
    }

    uint64_t originalSize = 0;
    in.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

    std::vector<uint64_t> freq(256, 0);
    for (int i = 0; i < 256; ++i) {
        uint32_t f = 0;
        in.read(reinterpret_cast<char*>(&f), sizeof(f));
        freq[i] = f;
    }

    Node *root = buildHuffmanTree(freq);
    if (!root) {
        std::ofstream out(outPath, std::ios::binary);
        return true; // empty file
    }

    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open output file\n";
        freeTree(root);
        return false;
    }

    BitReader br(in);
    uint64_t written = 0;

    while (written < originalSize) {
        Node *cur = root;
        while (cur->left || cur->right) {
            bool bit;
            if (!br.readBit(bit)) {
                std::cerr << "Unexpected end of compressed data\n";
                freeTree(root);
                return false;
            }
            cur = bit ? cur->right : cur->left;
        }
        out.put(static_cast<char>(cur->byte));
        written++;
    }

    freeTree(root);
    return true;
}
