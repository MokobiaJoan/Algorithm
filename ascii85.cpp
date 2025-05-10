#include "ascii85.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cctype>

std::string encodeBlock(const uint8_t* block, size_t length) {
    uint32_t value = 0;
    for (size_t i = 0; i < length; ++i)
        value |= block[i] << (24 - 8 * i);

    if (length == 4 && value == 0) return "z";

    char encoded[5];
    for (size_t i = length; i < 4; ++i)
        value |= 0 << (24 - 8 * i);

    for (int i = 4; i >= 0; --i) {
        encoded[i] = (value % 85) + 33;
        value /= 85;
    }

    return std::string(encoded, length < 4 ? length + 1 : 5);
}

std::string encodeAscii85(const std::vector<uint8_t>& data) {
    std::string result = "<~";
    for (size_t i = 0; i < data.size(); i += 4) {
        size_t len = std::min<size_t>(4, data.size() - i);
        result += encodeBlock(&data[i], len);
    }
    result += "~>";
    return result;
}

std::vector<uint8_t> decodeAscii85(const std::string& input) {
    std::vector<uint8_t> output;
    std::vector<uint32_t> group;
    bool started = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];

        if (!started) {
            if (ch == '<' && i + 1 < input.size() && input[i + 1] == '~') {
                started = true;
                ++i;
            }
            continue;
        }

        if (ch == '~' && i + 1 < input.size() && input[i + 1] == '>') break;
        if (isspace(ch)) continue;

        if (ch == 'z') {
            if (!group.empty()) throw std::runtime_error("Invalid 'z' inside a group");
            output.insert(output.end(), {0, 0, 0, 0});
            continue;
        }

        if (ch < '!' || ch > 'u') continue;

        group.push_back(ch - 33);
        if (group.size() == 5) {
            uint32_t val = 0;
            for (int j = 0; j < 5; ++j) val = val * 85 + group[j];
            output.push_back((val >> 24) & 0xFF);
            output.push_back((val >> 16) & 0xFF);
            output.push_back((val >> 8) & 0xFF);
            output.push_back(val & 0xFF);
            group.clear();
        }
    }

    if (!group.empty()) {
        size_t len = group.size();
        for (size_t i = len; i < 5; ++i) group.push_back(84);
        uint32_t val = 0;
        for (int i = 0; i < 5; ++i) val = val * 85 + group[i];
        for (size_t i = 0; i < len - 1; ++i)
            output.push_back((val >> (24 - 8 * i)) & 0xFF);
    }

    return output;
}