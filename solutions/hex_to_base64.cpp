#include <algorithm>
#include <cmath>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.h"

// \param hexString: string of hexadecimal symbols
// \return converted hexadecimal string to base64 string
std::string hexToBase64(const std::string& hexString) {
    // algoritmo baseado em 
    // https://pt.wikipedia.org/wiki/Base64

    using std::string;
    using std::vector;

    string binString = hexToBin(hexString);
    binString = padStringWithChar(binString, '0', 6, true);

    vector<string> sixBitBlocks(std::ceil((float)binString.length() / 6));
    for (size_t i = 0; i < binString.length(); i += 6) {
        sixBitBlocks[i / 6] = binString.substr(i, 6);
    }

    string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string base64String = "";
    for (auto block : sixBitBlocks) {
        base64String += base64Symbols[binToDecimal(block)];
    }

    base64String = padStringWithChar(base64String, '=', 4, true);
    return base64String;
}

int main(int argc, const char* argv[]) {
    std::string input;
    if (argc < 2) {
        std::cout << "You didn't pass any hex string as argument.\nBy default, this program will use the following string as input:\n";
        input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
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