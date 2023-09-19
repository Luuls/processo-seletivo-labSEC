#include "utilities.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

//TODO: pollish the 'using' inside the functions

std::vector<std::string> readFileLines(const std::string& filePath) {
    std::ifstream file(filePath);
    std::istream_iterator<std::string> start(file), end;
    std::vector<std::string> lines(start, end);
    return lines;
}

std::string padStringWithChar(const std::string& word, char c, size_t sizeToFixTo, bool side) {
    using std::string;

    if (sizeToFixTo == 0) {
        return word;
    }

    size_t rest = word.length() % sizeToFixTo;
    if (rest == 0) {
        return word;
    }

    size_t paddingSize = sizeToFixTo - rest;

    string result;
    // true -> right side
    if (side) {
        result = word + string(paddingSize, c);
    }
    // false -> left side
    else {
        result = string(paddingSize, c) + word;
    }

    return result;
}

std::string hexToBin(const std::string& hexString) {
    using std::map;
    using std::string;

    // conversion table
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

    // conversion table
    static map<string, char> binNibbleToHexSymbol{
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
        {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'}
    };

    // just to make sure, fix the size of the string to a multiple of 4 bits
    string fixedBinString = padStringWithChar(binString, '0', 4, false);
    string hexString;
    for (size_t i = 0; i < fixedBinString.length(); i += 4) {
        // read the bin string 1 nibble at a time
        string binNibble = fixedBinString.substr(i, 4);
        hexString += binNibbleToHexSymbol[binNibble];
    }

    size_t firstNonZero = hexString.find_first_not_of('0');
    if (firstNonZero != string::npos) {
        hexString = hexString.substr(firstNonZero);
    }

    hexString = padStringWithChar(hexString, '0', 2, false);
    return hexString;
}

std::string binToASCII(const std::string& binString) {
    using std::string;

    // just to make sure, fix the size of the string to a multiple of 8 bits
    string fixedBinString = padStringWithChar(binString, '0', 8, false);
    string ASCIIString;
    for (size_t i = 0; i < fixedBinString.length(); i += 8) {
        // read the bin string 1 byte at a time
        string binByte = fixedBinString.substr(i, 8);
        ASCIIString += (char) binToDecimal(binByte);
    }

    return ASCIIString;
}

std::string ASCIIToBin(const std::string& ASCIIString) {
    using std::string;

    string binString;
    for (auto c : ASCIIString) {
        binString += padStringWithChar(decimalToBin(c), '0', 8, false);
    }

    return binString;
}


std::string decimalToBin(unsigned int decimalNumber) {
    using std::string;

    if (decimalNumber == 0) {
        return "0";
    }

    string binString;
    while (decimalNumber > 0) {
        // method of division by 2
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
        // converts the char to the decimal value that it represents
        bool binValue = binString[i] - '0';
        sum += binValue * int(std::pow(2, stringLength - 1 - i));
    }

    return sum;
}

bool isHexSymbol(char symbol) {
    symbol = toupper(symbol);
    return ('0' <= symbol && symbol <= '9') || ('A' <= symbol && symbol <= 'F');
}

std::string base64ToHex(const std::string& base64String) {
    using std::string;
    using std::vector;

    string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    // access time faster than search through the string
    std::map<char, int> base64SymbolToDecimal;
    for (size_t i = 0; i < base64Symbols.length(); i++) {
        base64SymbolToDecimal[base64Symbols[i]] = i;
    }

    string binString;
    for (auto symbol : base64String) {
        size_t symbolIndex = base64SymbolToDecimal[symbol];
        binString += padStringWithChar(decimalToBin(symbolIndex), '0', 6, false);
    }

    string hexString = padStringWithChar(binToHex(binString), '0', 2, false);
    return hexString;
}

std::string singleByteXor(const std::string& binString, unsigned char key) {
    using std::string;

    // just to make sure, fix the size of the string to a multiple of 8 bits
    string keyBinString = padStringWithChar(decimalToBin(key), '0', 8, false);

    string result;
    for (size_t i = 0; i < binString.length(); i++) {
        char keyChar = keyBinString[i % 8];
        result += binString[i] == keyChar ? '0' : '1';
    }
    
    return result;
}

std::string repeating_key_xor(const std::string& binString, const std::string& key) {
    std::string result;

    std::string paddedString = padStringWithChar(binString, '0', 8, false);
    for (size_t i = 0; i < paddedString.length(); i += 8) {
        result += singleByteXor(paddedString.substr(i, 8), key[(i / 8) % key.length()]);
    }

    return result;
}

double evaluateText(const std::string& text) {
    using std::map;

    // frequency table gotten from:
    // https://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html

    // ps: the frequency of ' ' was taken from multiple sources.
    // I couldn't find a reliable source for it

    map<char, double> englishLetterFrequency = {
        {'e', 12.02}, {'t', 9.10}, {'a', 8.12}, {'o', 7.68},
        {'i', 7.31}, {'n', 6.95}, {'s', 6.28}, {'r', 6.02},
        {'h', 5.92}, {'d', 4.32}, {'l', 3.98}, {'u', 2.88},
        {'c', 2.71}, {'m', 2.61}, {'f', 2.30}, {'y', 2.11},
        {'w', 2.09}, {'g', 2.02}, {'p', 1.82}, {'b', 1.49},
        {'v', 1.11}, {'k', 0.69}, {'x', 0.17}, {'q', 0.11},
        {'j', 0.10}, {'z', 0.07}, {' ', 13.29}
    };
    
    // create a map so that we don't have to iterate over the text every time we want to count a letter
    map<char, double> textLettersCount;

    // every letter from the frequency table must be in the map
    // and start with a frequency of 0
    for (auto [letter, frequency] : englishLetterFrequency) {
        textLettersCount[letter] = 0;
    }

    // counts the frequency of every letter in the text if its in the frequency table
    for (auto c : text) {
        if (englishLetterFrequency.find(c) != englishLetterFrequency.end()) {
            textLettersCount[c]++;
        }
    }

    // accumulates the error between the text letter frequency and the english letter frequency
    double sum = 0;
    for (auto [letter, count] : textLettersCount) {
        double textCurrentLetterFrequency = count / text.length();
        double error = std::abs(textCurrentLetterFrequency - englishLetterFrequency[letter]);
        sum += error;
    }

    return sum;
}

// \param hexString: a string to try to decrypt
CryptoText<unsigned char> decrypt_message(std::string binString) {
    // store all the possible candidates
    std::vector<CryptoText<unsigned char>> textCandidates(256);

    // 1 byte = 8 bits -> 2^8 = 256 -> can only count from 0 to 255
    for (int keyCandidate = 0; keyCandidate < 256; keyCandidate++) {
        std::string textCandidate = singleByteXor(binString, keyCandidate);
        textCandidate = binToASCII(textCandidate);
        textCandidates[keyCandidate] = { textCandidate, (unsigned char)keyCandidate, evaluateText(textCandidate) };
    }

    // get the smallest score between the candidates
    // (smaller error accumulation)
    CryptoText bestCandidate = *std::min_element(textCandidates.begin(), textCandidates.end(),
        [](const CryptoText<unsigned char>& a, const CryptoText<unsigned char>& b) {
            return a.score < b.score;
    });

    return bestCandidate;
}

int hammingDistance(const std::string& binA, const std::string& binB) {
    if (binA.length() != binB.length()) {
        return -1;
    }

    int differencesCount = 0;
    for (size_t i = 0; i < binA.length(); i++) {
        if (binA[i] != binB[i]) {
            differencesCount++;
        }
    }

    return differencesCount;
}