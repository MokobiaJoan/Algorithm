#include "ascii85.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Helper to encode and decode from string
std::string encode(const std::string& input) {
    std::vector<uint8_t> data(input.begin(), input.end());
    return encodeAscii85(data);
}

std::string decode(const std::string& input) {
    std::vector<uint8_t> output = decodeAscii85(input);
    return std::string(output.begin(), output.end());
}

// === Unit Tests ===

TEST(Ascii85Test, EncodeHello) {
    std::string input = "hello";
    std::string expected = "<~BOu!rDZ~>";  // standard ASCII85 for "hello"
    EXPECT_EQ(encode(input), expected);
}

TEST(Ascii85Test, DecodeHello) {
    std::string encoded = "<~BOu!rDZ~>";
    std::string expected = "hello";
    EXPECT_EQ(decode(encoded), expected);
}

TEST(Ascii85Test, RoundTripBasic) {
    std::string input = "Hello Jane!";
    EXPECT_EQ(decode(encode(input)), input);
}


TEST(Ascii85Test, DecodeEmptyString) {
    std::string encoded = "<~>";
    std::string expected = "";
    EXPECT_EQ(decode(encoded), expected);
}

TEST(Ascii85Test, NullByteEncoding) {
    std::string input = std::string("\0\0\0\0", 4);
    std::string encoded = encode(input);
    EXPECT_TRUE(encoded.find('z') != std::string::npos); // 'z' used for 4 null bytes
    EXPECT_EQ(decode(encoded), input);
}

TEST(Ascii85Test, RoundTripWithPadding) {
    std::string input = "abc";  // 3 bytes, will be padded during encoding
    EXPECT_EQ(decode(encode(input)), input);
}

TEST(Ascii85Test, EncodeShortString) {
    std::string input = "ABC";
    std::string encoded = encode(input);
    std::string decoded = decode(encoded);
    EXPECT_EQ(decoded, input);
}


TEST(Ascii85Test, RoundTripSimple) {
    std::string input = "Test123!";
    EXPECT_EQ(decode(encode(input)), input);
}

TEST(Ascii85Test, EncodeNullBlockUsesZ) {
    std::string input = std::string(4, '\0');  // 4 null bytes
    std::string encoded = encode(input);
    EXPECT_NE(encoded.find('z'), std::string::npos);
    EXPECT_EQ(decode(encoded), input);
}

TEST(Ascii85Test, DecodeKnownValue) {
    std::string encoded = "<~BOu!rDZ~>";
    std::string expected = "hello";
    EXPECT_EQ(decode(encoded), expected);
}