#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include <vector>
#include <map>

struct Symbol {
    char character;
    double probability;
    std::string code;
};

void generateShannonCodes(std::vector<Symbol>& symbols);

#endif // ENCODER_H