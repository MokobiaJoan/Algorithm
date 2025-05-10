#include "ascii85.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2 || (std::string(argv[1]) != "-e" && std::string(argv[1]) != "-d")) {
        std::cerr << "Usage: " << argv[0] << " -e | -d\n";
        return 1;
    }

    std::vector<uint8_t> inputBytes;
    std::string inputText;
    char ch;

    // Read input from stdin
    while (std::cin.get(ch)) {
        inputBytes.push_back(static_cast<uint8_t>(ch));
        inputText += ch;
    }

    if (std::string(argv[1]) == "-e") {
        std::string encoded = encodeAscii85(inputBytes);
        std::cout << encoded << std::endl; // clean output
    } else {
        std::vector<uint8_t> decoded = decodeAscii85(inputText);
        for (uint8_t byte : decoded) {
            std::cout << static_cast<char>(byte);
        }
        std::cout << std::endl; // newline after decoded output
    }

    return 0;
}