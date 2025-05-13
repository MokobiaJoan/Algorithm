#ifndef ASCII85_HPP
#define ASCII85_HPP

#include <vector>
#include <string>
#include <cstdint>

std::string encodeAscii85(const std::vector<uint8_t>& data);
std::vector<uint8_t> decodeAscii85(const std::string& input);

#endif // ASCII85_HPP