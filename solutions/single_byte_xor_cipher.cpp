#include "utilities.h"

#include <iostream>

std::string decrypt_message(std::string hexString) {
    for (int keyCandidate = 0; keyCandidate < 256; keyCandidate++) {
        std::string textCandidate = singleByteXor(hexToBin(hexString), keyCandidate);
        textCandidate = hexToBin(textCandidate);
        for (size_t i = 0; i < textCandidate.length(); i += 8) {
            std::cout << (char) binToDecimal(textCandidate.substr(i, 8));
        }
        std::cout << std::endl;
    }

    return "";
}

int main() {
    std::string input;
    decrypt_message("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    
    return 0;
}