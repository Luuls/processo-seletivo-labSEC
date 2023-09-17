#include <algorithm>
#include <cmath>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string hexToBase64(const std::string& hexString);

std::string hexToBin(const std::string& hexString);

std::string decimalToBin(unsigned int decimalValue);

size_t binToDecimal(const std::string binString);

std::string padStringWithChar(const std::string& word, char c, size_t sizeToFixTo, bool side);

bool isHexSymbol(char symbol);

int main(int argc, const char* argv[]) {
    std::string input;
    if (argc < 2) {
        input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        std::cout << "You didn't pass any hex string as argument.\nBy default, this program will use the following string as input:\n";
        std::cout << input;
        std::cout << "\n\nbase64 result:\n";
    }
    else if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [hex string]\n";
        return 1;
    }
    else {
        input = argv[1];
    }


    std::cout << hexToBase64(input) << '\n';

    return 0;
}

std::string hexToBase64(const std::string& hexString) {
    using std::string;
    using std::vector;

    string binString = hexToBin(hexString);

    binString = padStringWithChar(binString, '0', 6, true);

    vector<string> sixBitBytes(std::ceil((float)binString.length() / 6));

    for (size_t i = 0; i < binString.length(); i += 6) {
        sixBitBytes[i / 6] = binString.substr(i, 6);
    }

    string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string base64String = "";

    for (auto code : sixBitBytes) {
        base64String += base64Symbols[binToDecimal(code)];
    }

    base64String = padStringWithChar(base64String, '=', 4, true);
    return base64String;
}

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

size_t binToDecimal(const std::string binString) {
    size_t stringLength = binString.length();
    size_t sum = 0;
    for (size_t i = 0; i != stringLength; i++) {
        // converte o código ASCII do char para o valor que o char representa em int
        bool binValue = binString[i] - '0';
        sum += binValue * int(std::pow(2, stringLength - 1 - i));
    }

    return sum;
}

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

bool isHexSymbol(char symbol) {
    symbol = toupper(symbol);
    return ('0' <= symbol && symbol <= '9') || ('A' <= symbol && symbol <= 'F');
}
