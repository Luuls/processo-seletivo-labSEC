#include "utilities.h"

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
    // uma tabela de conversão de símbolo hexadecimal para um binário de 4 bits
    static std::map<char, std::string> hexSymbolToBinNibble{
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    std::string binString;
    for (auto symbol : hexString) {
        if (isHexSymbol(symbol)) {
            binString += hexSymbolToBinNibble[toupper(symbol)];
        }
    }

    // cout << binString;
    return binString;
}

// \param decimalNumber: a decimal number
// \return a string containing the binary representation of the decimal number
std::string decimalToBin(unsigned int decimalNumber) {
    using std::string;

    string binString;
    while (decimalNumber != 0) {
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
