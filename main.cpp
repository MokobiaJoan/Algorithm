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

    while (std::cin.get(ch)) {
        inputBytes.push_back(static_cast<uint8_t>(ch));
        inputText += ch;
    }

    if (std::string(argv[1]) == "-e") {
        std::string encoded = encodeAscii85(inputBytes);
        std::cout << encoded << std::endl;
    } else {
        try {
            std::vector<uint8_t> decoded = decodeAscii85(inputText);
            for (uint8_t byte : decoded) {
                std::cout << static_cast<char>(byte);
            }
            std::cout << std::endl;
            
        } catch (const std::exception& e) {
            std::cerr << "Decoding failed: " << e.what() << std::endl;
            return 2;
        }
    }

    return 0;
}