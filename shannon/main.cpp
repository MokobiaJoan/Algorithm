#include "encoder.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iterator>

int main() {
    std::ifstream input("input.bin", std::ios::binary);
    if (!input) {
        std::cerr << "Error: Could not open input.bin\n";
        return 1;
    }

    std::vector<unsigned char> data((std::istreambuf_iterator<char>(input)),
                                     std::istreambuf_iterator<char>());

    if (data.empty()) {
        std::cerr << "Error: input.bin is empty\n";
        return 1;
    }

    // Count frequencies
    std::map<unsigned char, int> freq;
    for (unsigned char ch : data) {
        freq[ch]++;
    }

    int total = data.size();

    // Prepare symbols vector sorted by descending probability
    std::vector<std::pair<unsigned char, double>> symbols;
    for (const auto& [ch, count] : freq) {
        symbols.emplace_back(ch, static_cast<double>(count) / total);
    }

    std::sort(symbols.begin(), symbols.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    // Convert to Symbol vector for code generation
    std::vector<Symbol> symbolVec;
    for (const auto& [ch, prob] : symbols) {
        symbolVec.push_back(Symbol{ static_cast<char>(ch), prob, "" });
    }

    // Generate Shannon codes
    generateShannonCodes(symbolVec);

    // Build map from char to code
    std::map<unsigned char, std::string> codes;
    for (const auto& sym : symbolVec) {
        codes[static_cast<unsigned char>(sym.character)] = sym.code;
    }

    // Encode data into bitstring
    std::string bitstring;
    for (unsigned char ch : data) {
        bitstring += codes[ch];
    }

    // Write encoded bitstring to output.bin (readable)
    std::ofstream encoded_output("output.bin");
    if (!encoded_output) {
        std::cerr << "Error: Could not open output.bin for writing\n";
        return 1;
    }
    encoded_output << bitstring;
    encoded_output.close();

    
std::ofstream dict_output("output.dict");
if (!dict_output) {
    std::cerr << "Error: Could not open output.dict for writing\n";
    return 1;
}

for (const auto& sym : symbolVec) {
    unsigned char symbol = static_cast<unsigned char>(sym.character);
    const std::string& code = sym.code;
    if (std::isprint(symbol)) {
        dict_output << sym.character << " " << code << "\n";
    } else {
        dict_output << "." << " " << code << "\n";  // Replace non-printable with '.'
    }
}
dict_output.close();

    std::cout << "Encoding complete. Files output.bin and output.dict created.\n";

    return 0;
}