#include "decoder.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, char> load_dictionary(const std::string& filename) {
    std::map<std::string, char> dict;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open dictionary file.\n";
        return dict;
    }
    char symbol;
    std::string code;
    while (file >> symbol >> code) {
        dict[code] = symbol;
    }
    return dict;
}

std::string load_bitstring(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open encoded file.\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void decode_and_write(const std::string& bitstring,
                      const std::map<std::string, char>& dict,
                      const std::string& output_filename) {
    std::ofstream out(output_filename, std::ios::binary);
    std::string buffer;
    for (char bit : bitstring) {
        buffer += bit;
        if (dict.count(buffer)) {
            out.put(dict.at(buffer));
            buffer.clear();
        }
    }
}