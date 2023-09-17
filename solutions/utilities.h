#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <string>

std::string padStringWithChar(const std::string& word, char c, size_t sizeToFixTo, bool side);

std::string hexToBin(const std::string& hexString);

std::string binToHex(const std::string& binString);

std::string decimalToBin(unsigned int decimalValue);

unsigned int binToDecimal(const std::string binString);

bool isHexSymbol(char symbol);

#endif //_UTILITIES_H_