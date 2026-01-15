#pragma once
#include <cstdint>
#include <fstream>

class BitWriter {
    std::ofstream &out;
    uint8_t buffer = 0;
    int bitCount = 0;

public:
    BitWriter(std::ofstream &os) : out(os) {}

    void writeBit(bool bit) {
        buffer |= (bit ? 1 : 0) << (7 - bitCount);
        bitCount++;
        if (bitCount == 8) flushByte();
    }

    void writeBits(const std::string &bits) {
        for (char c : bits) {
            writeBit(c == '1');
        }
    }

    void flush() {
        if (bitCount > 0) {
            flushByte();
        }
    }

private:
    void flushByte() {
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bitCount = 0;
    }
};

class BitReader {
    std::ifstream &in;
    uint8_t buffer = 0;
    int bitCount = 8;
    bool eof = false;

public:
    BitReader(std::ifstream &is) : in(is) {}

    bool readBit(bool &bit) {
        if (bitCount == 8) {
            int ch = in.get();
            if (ch == EOF) {
                eof = true;
                return false;
            }
            buffer = static_cast<uint8_t>(ch);
            bitCount = 0;
        }
        bit = (buffer >> (7 - bitCount)) & 1;
        bitCount++;
        return true;
    }

    bool isEof() const { return eof; }
};
