#include "utilities.h"

#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

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

std::string binToASCII(const std::string& binString) {
    using std::string;

    string fixedBinString = padStringWithChar(binString, '0', 8, false);
    string ASCIIString;
    for (size_t i = 0; i < fixedBinString.length(); i += 8) {
        string binByte = fixedBinString.substr(i, 8);
        ASCIIString += (char) binToDecimal(binByte);
    }

    return ASCIIString;
}

std::string decimalToBin(unsigned int decimalNumber) {
    using std::string;

    if (decimalNumber == 0) {
        return "0";
    }

    string binString;
    while (decimalNumber > 0) {
        unsigned int rest = decimalNumber % 2;
        binString += '0' + rest;

        decimalNumber /= 2;
    }

    std::reverse(binString.begin(), binString.end());
    return binString;
}

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

bool isHexSymbol(char symbol) {
    symbol = toupper(symbol);
    return ('0' <= symbol && symbol <= '9') || ('A' <= symbol && symbol <= 'F');
}

// \param binString: a string containing only 0s and 1s
// \param key: a char
std::string singleByteXor(const std::string& binString, int key) {
    using std::string;

    string keyBinString = padStringWithChar(decimalToBin(key), '0', 8, false);

    string result;
    for (size_t i = 0; i < binString.length(); i++) {
        char keyChar = keyBinString[i % 8];
        result += binString[i] == keyChar ? '0' : '1';
    }
    
    return result;
}

double evaluateText(const std::string& text) {
    using std::map;

    // Tabela de frequência obtida em
    // https://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html

    map<char, double> englishLetterFrequency = {
        {'e', 12.02}, {'t', 9.10}, {'a', 8.12}, {'o', 7.68},
        {'i', 7.31}, {'n', 6.95}, {'s', 6.28}, {'r', 6.02},
        {'h', 5.92}, {'d', 4.32}, {'l', 3.98}, {'u', 2.88},
        {'c', 2.71}, {'m', 2.61}, {'f', 2.30}, {'y', 2.11},
        {'w', 2.09}, {'g', 2.02}, {'p', 1.82}, {'b', 1.49},
        {'v', 1.11}, {'k', 0.69}, {'x', 0.17}, {'q', 0.11},
        {'j', 0.10}, {'z', 0.07}, {' ', 13.29}
    };
    
    // map para não precisar percorrer a string uma vez por letra
    map<char, double> textLettersCount;

    // todas as letras da tabela de frequência devem estar no map
    // e começam com frequência 0
    for (auto [letter, frequency] : englishLetterFrequency) {
        textLettersCount[letter] = 0;
    }

    // conta a frequência de cada letra no texto se ela estiver na tabela de frequência
    for (auto c : text) {
        if (englishLetterFrequency.find(c) != englishLetterFrequency.end()) {
            textLettersCount[c]++;
        }
    }

    // acumula o erro entre a frequência de cada letra no texto e a frequência esperada
    double sum = 0;
    for (auto [letter, count] : textLettersCount) {
        double textCurrentLetterFrequency = count / text.length();
        double error = std::abs(textCurrentLetterFrequency - englishLetterFrequency[letter]);
        sum += error;
    }

    return sum;
}