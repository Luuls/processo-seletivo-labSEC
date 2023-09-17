#include <iostream>
#include <string>
#include "utilities.h"

std::string fixed_xor(const std::string& a, const std::string& b) {
    std::string result("");
    for (size_t i = 0; i < a.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }

    return result;
}

int main(int argc, const char* argv[]) {
    std::string a, b;
    if (argc < 2) {
        std::cout << "You didn't pass any hex strings as argument.\nBy default, this program will use the following strings as input:\n";
        a = "1c0111001f010100061a024b53535009181c";
        b = "686974207468652062756c6c277320657965";
        std::cout << "a: " << a << '\n';
        std::cout << "b: " << b << '\n';
        std::cout << "\n\nXOR'd result:\n";
    }
    else if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " [hex string a, hex string b]\n";
        return 1;
    }
    else {
        a = argv[1];
        b = argv[2];
    }

    std::cout << binToHex(fixed_xor(hexToBin(a), hexToBin(b))) << '\n';
    
    return 0;
}