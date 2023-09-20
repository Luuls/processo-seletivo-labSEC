#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <string>
#include <vector>

// a struct to hold the result of a cryptographic message
template<typename KeyT>
struct CryptoText {
    std::string text;
    // the key used to decrypt/encrypt the message
    KeyT key;
    double evaluation;
};

// \param filePath: the path to the file to be read
// \return a vector of strings, each string representing a line from the file
std::vector<std::string> readFileLines(const std::string& filePath);

// \param word: a string to be padded
// \param c: the char to be used as padding
// \param sizeToFixTo: the size to fix the string to
// \param side: true if the padding should be added to the right side of the string, false if it should be added to the left side
// \return the padded string
std::string padStringWithChar(const std::string& word, char c, size_t sizeToFixTo, bool side);

// \param hexString: a string containing only hexadecimal symbols
// \return a string containing the binary representation of the hexadecimal string correctly padded with 0s
std::string hexToBin(const std::string& hexString);

// \param binString: a string containing only 0s and 1s
// \return a string containing the hexadecimal representation of the binary string
std::string binToHex(const std::string& binString);

// \param binString: a string containing only 0s and 1s
// \return a string containing the ASCII representation of the binary string
std::string binToASCII(const std::string& binString);

// \param ASCIIString: a string containing only ASCII symbols
// \return a string containing the binary representation of the ASCII string
std::string ASCIIToBin(const std::string& ASCIIString);

// \param decimalNumber: a decimal number
// \return a string containing the binary representation of the decimal number
std::string decimalToBin(unsigned int decimalValue);

// \param binString: a string containing only 0s and 1s
// \return the decimal value of the binary string
unsigned int binToDecimal(const std::string binString);

// \param symbol: a char
// \return true if the char is a hexadecimal symbol, false otherwise
bool isHexSymbol(char symbol);

std::string base64ToHex(const std::string& base64String);

std::string base64ToBin(const std::string& base64String);

// \param binString: a string containing only 0s and 1s
// \param key: a char
// \return a string containing the result of the XOR operation between the binary string and the key
std::string singleByteXor(const std::string& binString, unsigned char key);

std::string repeating_key_xor(const std::string& binString, const std::string& key);

double evaluateText(const std::string& text);

CryptoText<unsigned char> decrypt_message(std::string binString);

int hammingDistance(const std::string& binA, const std::string& binB);

std::vector<std::vector<std::string>> transposeMatrix(const std::vector<std::vector<std::string>>& matrix);

#endif //_UTILITIES_H_