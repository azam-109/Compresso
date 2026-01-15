#include <iostream>

bool compressFile(const std::string &inPath, const std::string &outPath);
bool decompressFile(const std::string &inPath, const std::string &outPath);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " c <input> <output>\n"
                  << "  " << argv[0] << " d <input> <output>\n";
        return 1;
    }

    char mode = argv[1][0];
    std::string inPath = argv[2];
    std::string outPath = argv[3];

    bool ok = false;
    if (mode == 'c') 
    {
        ok = compressFile(inPath, outPath);
    } else if (mode == 'd') 
    {
        ok = decompressFile(inPath, outPath);
    } else 
    {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return ok ? 0 : 1;
}
