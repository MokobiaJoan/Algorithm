#include <iostream>
#include <string>
#include "ascii85.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./ascii85 <-e|-d>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];

    // Read entire stdin into a string i.e buffer-mode
    std::string input((std::istreambuf_iterator<char>(std::cin)),
                       std::istreambuf_iterator<char>());

    if (mode == "-e") {
        std::string encoded = ascii85::encode_ascii85(input);
        std::cout << encoded << std::endl;
    } else if (mode == "-d") {
        try {
            std::string decoded = ascii85::decode_ascii85_to_string(input);
            std::cout << decoded << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Decode error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 1;
    }

    return 0;
}