#include <iostream>
#include <string>
#include <vector>

#include "utilities.h"

std::string repeating_key_xor(const std::string& binString, const std::string& key) {
    std::string result;
    
    std::string paddedString = padStringWithChar(binString, '0', 8, false);
    for (size_t i = 0; i < paddedString.length(); i += 8) {
        result += singleByteXor(paddedString.substr(i, 8), key[(i / 8) % key.length()]);
    }

    return result;
}

int main() {
    
    std::string input = ASCIIToBin("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal");
    std::string result = binToHex(repeating_key_xor(input, "ICE"));
    std::cout << result << '\n';
    
    return 0;
}