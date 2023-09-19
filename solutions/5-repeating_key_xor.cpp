#include <iostream>
#include <string>
#include <vector>

#include "utilities.h"

int main() {
    
    std::string input = ASCIIToBin("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal");
    std::string result = binToHex(repeating_key_xor(input, "ICE"));
    std::cout << result << '\n';
    
    return 0;
}