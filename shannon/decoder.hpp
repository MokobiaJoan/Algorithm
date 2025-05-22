#ifndef DECODER_HPP
#define DECODER_HPP

#include <string>
#include <map>

std::map<std::string, char> load_dictionary(const std::string& filename);
std::string load_bitstring(const std::string& filename);
void decode_and_write(const std::string& bitstring,
                      const std::map<std::string, char>& dict,
                      const std::string& output_filename);

#endif