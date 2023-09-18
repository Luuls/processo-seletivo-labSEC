#include "utilities.h"

#include <iostream>
#include <vector>

std::string decrypt_message(std::string hexString) {
    std::vector<std::string> textCandidates(256);
    for (int keyCandidate = 0; keyCandidate < 256; keyCandidate++) {
        std::string textCandidate = singleByteXor(hexToBin(hexString), keyCandidate);
        textCandidate = hexToBin(textCandidate);
        textCandidate = binToASCII(textCandidate);
        textCandidates[keyCandidate] = textCandidate;
    }

    return "";
}

int main() {
    std::string input;
    decrypt_message("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    
    return 0;
}