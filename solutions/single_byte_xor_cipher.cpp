#include "utilities.h"

#include <iostream>
#include <vector>

EncryptedText decrypt_message(std::string hexString) {
    // armazenar todos os candidatos a mensagem criptografada
    std::vector<EncryptedText> textCandidates(256);

    // 1 byte = 8 bits -> 2^8 = 256 possibilidades
    for (int keyCandidate = 0; keyCandidate < 256; keyCandidate++) {
        std::string textCandidate = singleByteXor(hexToBin(hexString), keyCandidate);
        textCandidate = binToASCII(textCandidate);
        textCandidates[keyCandidate] = {textCandidate, (unsigned char) keyCandidate, evaluateText(textCandidate)};
    }

    // encontrar o candidato com a menor pontuação
    // (menor acúmulo de erros)
    EncryptedText bestCandidate = textCandidates[0];
    for (size_t i = 1; i < textCandidates.size(); i++) {
        if (textCandidates[i].score < bestCandidate.score) {
            bestCandidate = textCandidates[i];
        }
    }

    return bestCandidate;
}

int main() {
    std::string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    EncryptedText message = decrypt_message(input);
    
    std::cout << "\nDecrypted message: " << message.text << '\n';
    std::cout << "Key used to encrypt: " << message.key << '\n';
    std::cout << "Evaluated score: " << message.score << '\n';
    
    return 0;
}