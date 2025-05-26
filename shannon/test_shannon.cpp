#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>

void write_test_input(const std::string& filename, const std::string& content) {
    std::ofstream ofs(filename);
    assert(ofs && "Failed to open test input file");
    ofs << content;
    ofs.close();
}

std::string read_file(const std::string& filename) {
    std::ifstream ifs(filename);
    assert(ifs && "Failed to read file");
    std::string content((std::istreambuf_iterator<char>(ifs)),
                         std::istreambuf_iterator<char>());
    return content;
}

int main() {
    const std::string input_str = "ABRACADABRA";
    write_test_input("test_input.txt", input_str);

    // Run encoder
    int enc_result = std::system("./shannon_encoder test_input.txt");
    assert(enc_result == 0 && "Encoder failed");

    // Run decoder
    int dec_result = std::system("./shannon_decoder output.bin output.dict decoded.bin");
    assert(dec_result == 0 && "Decoder failed");

    // Read decoded file
    std::string decoded_str = read_file("decoded.bin");

    // Compare
    assert(input_str == decoded_str && "Decoded output does not match original input");

    std::cout << "✅ Test passed: decoded output matches original input.\n";
    return 0;
}