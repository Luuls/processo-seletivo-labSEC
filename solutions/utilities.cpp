#include "utilities.h"

#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

// \param word: a string to be padded
// \param c: the char to be used as padding
// \param sizeToFixTo: the size to fix the string to
// \param side: true if the padding should be added to the right side of the string, false if it should be added to the left side
// \return the padded string
std::string padStringWithChar(const std::string& word, char c, size_t sizeToFixTo, bool side) {
    using std::string;

    size_t rest = word.length() % sizeToFixTo;
    if (!rest) {
        return word;
    }

    size_t paddingSize = sizeToFixTo - rest;

    string result;
    if (side) {
        result = word + string(paddingSize, c);
    }
    else {
        result = string(paddingSize, c) + word;
    }

    return result;
}

// \param hexString: a string containing only hexadecimal symbols
// \return a string containing the binary representation of the hexadecimal string correctly padded with 0s
std::string hexToBin(const std::string& hexString) {
    using std::map;
    using std::string;

    // uma tabela de conversão de símbolo hexadecimal para um binário de 4 bits
    static map<char, string> hexSymbolToBinNibble{
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
        {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
    };

    string binString;
    for (auto symbol : hexString) {
        if (isHexSymbol(symbol)) {
            binString += hexSymbolToBinNibble[tolower(symbol)];
        }
    }

    return binString;
}

std::string binToHex(const std::string& binString) {
    using std::map;
    using std::string;

    // uma tabela de conversão de um binário de 4 bits para um símbolo hexadecimal
    static map<string, char> binNibbleToHexSymbol{
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
        {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'}
    };

    string fixedBinString = padStringWithChar(binString, '0', 4, false);
    string hexString;
    for (size_t i = 0; i < fixedBinString.length(); i += 4) {
        string binNibble = fixedBinString.substr(i, 4);
        hexString += binNibbleToHexSymbol[binNibble];
    }

    size_t firstNonZero = hexString.find_first_not_of('0');
    if (firstNonZero != string::npos) {
        hexString = hexString.substr(firstNonZero);
    }

    return hexString;
}

// \param decimalNumber: a decimal number
// \return a string containing the binary representation of the decimal number
std::string decimalToBin(unsigned int decimalNumber) {
    using std::string;

    if (decimalNumber == 0) {
        return "0";
    }

    string binString;
    while (decimalNumber > 0) {
        int rest = decimalNumber % 2;
        binString += '0' + rest;

        decimalNumber /= 2;
    }

    std::reverse(binString.begin(), binString.end());
    return binString;
}

// \param binString: a string containing only 0s and 1s
// \return the decimal value of the binary string
unsigned int binToDecimal(const std::string binString) {
    size_t stringLength = binString.length();
    size_t sum = 0;
    for (size_t i = 0; i != stringLength; i++) {
        // converte o código ASCII do char para o valor que o char representa em int
        bool binValue = binString[i] - '0';
        sum += binValue * int(std::pow(2, stringLength - 1 - i));
    }

    return sum;
}

// \param symbol: a char
// \return true if the char is a hexadecimal symbol, false otherwise
bool isHexSymbol(char symbol) {
    symbol = toupper(symbol);
    return ('0' <= symbol && symbol <= '9') || ('A' <= symbol && symbol <= 'F');
}

std::string singleByteXor(const std::string& binString, unsigned char key) {
    using std::string;

    string keyBinString = padStringWithChar(decimalToBin(key), '0', 8, false);

    string result;
    for (size_t i = 0; i < binString.length(); i++) {
        char keyChar = keyBinString[i % 8];
        result += binString[i] == keyChar? '0' : '1';
    }

    result = binToHex(result);
    return result;
}