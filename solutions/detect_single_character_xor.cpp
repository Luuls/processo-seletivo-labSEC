#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utilities.h"

CryptoText findEncryptedMessage(const std::string& filePath) {
    std::vector<std::string> messages = readFileLines(filePath);
    std::vector<CryptoText> decryptedMessages;
    for (const auto& message : messages) {
        decryptedMessages.push_back(decrypt_message(hexToBin(message)));
    }

    // smallest score between the smallest scores
    CryptoText bestCandidate = *std::min_element(decryptedMessages.begin(), decryptedMessages.end(),
        [](const CryptoText& a, const CryptoText& b) {
            return a.score < b.score;
    });

    return bestCandidate;
}

int main() {
    std::cout << findEncryptedMessage("./data/4.txt").text << '\n';
    return 0;
}