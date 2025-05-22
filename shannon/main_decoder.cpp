#include "decoder.hpp"
#include <iostream>

int main() {
    std::map<std::string, char> dict = load_dictionary("output.dict");
    std::string bitstring = load_bitstring("output.bin");
    decode_and_write(bitstring, dict, "decoded.bin");
    std::cout << "Decoding complete. Output written to decoded.bin\n";
    return 0;
}