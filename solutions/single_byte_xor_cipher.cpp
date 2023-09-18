#include "utilities.h"

#include <iostream>
#include <vector>

int main() {
    std::string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    CryptoText message = decrypt_message(input);
    
    std::cout << "\nDecrypted message: " << message.text << '\n';
    std::cout << "Key used to encrypt: " << message.key << '\n';
    std::cout << "Evaluated score: " << message.score << '\n';
    
    return 0;
}