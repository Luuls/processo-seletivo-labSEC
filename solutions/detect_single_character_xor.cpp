#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utilities.h"

CryptoText<unsigned char> findEncryptedMessage(const std::string& filePath) {
    std::vector<std::string> messages = readFileLines(filePath);
    std::vector<CryptoText<unsigned char>> decryptedMessages;
    for (const auto& message : messages) {
        decryptedMessages.push_back(decrypt_message(hexToBin(message)));
    }

    // smallest score between the smallest scores
    CryptoText<unsigned char> bestCandidate = *std::min_element(decryptedMessages.begin(), decryptedMessages.end(),
        [](const CryptoText<unsigned char>& a, const CryptoText<unsigned char>& b) {
            return a.evaluation < b.evaluation;
    });

    return bestCandidate;
}

int main(int argc, char* argv[]) {
    std::string input;
    if (argc < 2) {
        std::cout << "You didn't pass any filepath as argument.\nBy default, this program will use the following file as input:\n";
        input = "./data/4.txt";
        std::cout << input;
        std::cout << "\n\nbest result:\n";
    }
    else if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [filepath]\n";
        return 1;
    }
    else {
        input = argv[1];
    }

    std::cout << findEncryptedMessage(input).text << '\n';
    return 0;
}