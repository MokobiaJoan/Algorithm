#include "encoder.hpp"
#include <cmath>

void generateShannonCodes(std::vector<Symbol>& symbols) {
    double cumulative = 0.0;
    for (auto& sym : symbols) {
        int len = std::ceil(-std::log2(sym.probability));
        double value = cumulative;
        std::string code;

        for (int i = 0; i < len; ++i) {
            value *= 2;
            if (value >= 1.0) {
                code += '1';
                value -= 1.0;
            } else {
                code += '0';
            }
        }

        sym.code = code;
        cumulative += sym.probability;
    }
}