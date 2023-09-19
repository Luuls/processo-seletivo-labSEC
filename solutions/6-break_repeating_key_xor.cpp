#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

#include "utilities.h"

std::string break_repeating_key_xor(const std::string& binString) {
    using std::vector;
    using std::string;

    struct KeySizeWithDistance {
        size_t keySize;
        double distance;
    };

    // compute the hamming distance for all key sizes between 2 and 40
    // utilizing the first four blocks of the string
    // and taking the average of the two hamming distances
    vector<KeySizeWithDistance> editDistances;
    for (size_t keySize = 2; keySize < 41; keySize++) {
        size_t sum = 0;
        for (size_t i = 0; i < 2; i++) {
            string firstBlock = binString.substr(i * keySize, keySize);
            string secondBlock = binString.substr((i + 1) * keySize, keySize);
            int editDistance = hammingDistance(firstBlock, secondBlock) / keySize;

            sum += editDistance;
        }

        editDistances.push_back({ keySize, sum / 2.0 });
    }
    
    vector<KeySizeWithDistance> lowestEditDistanceKeySizes(3);
    // take the 3 lowest edit distances
    std::partial_sort_copy(
        editDistances.begin(),
        editDistances.end(),
        lowestEditDistanceKeySizes.begin(),
        lowestEditDistanceKeySizes.end(),
        [](const KeySizeWithDistance& a, const KeySizeWithDistance& b) {
            return a.distance < b.distance;
    });
    
    vector<string> keysUsed;
    for (auto [keySize, editDistance] : lowestEditDistanceKeySizes) {
        vector<string> blocks(std::ceil((float)binString.length() / keySize));
        for (size_t i = 0; i < binString.length(); i += keySize) {
            blocks[i / keySize] = binString.substr(i, keySize);
        }

        vector<string> transposedBlocks(keySize);
        for (size_t i = 0; i < blocks.size(); i++) {
            for (size_t j = 0; j < keySize; j++) {
                if (j > blocks[i].length()) {
                    // to escape the outer loop
                    goto exit;
                    break;
                }
                    
                transposedBlocks[j] += blocks[i][j];
            }
        }
        exit:

        string keyUsed;
        for (auto block : transposedBlocks) {
            CryptoText<unsigned char> bestCandidate = decrypt_message(block);
            keyUsed += bestCandidate.key;
        }

        keysUsed.push_back(keyUsed);
    }

    vector<CryptoText<string>> results;
    for (auto key : keysUsed) {
        string text = binToASCII(repeating_key_xor(binString, key));
        double score = evaluateText(text);
        results.push_back({ text, key, score });
        
        std::cout << text << '\n';
        
    }

    CryptoText<string> bestResult = *std::min_element(results.begin(), results.end(),
        [](const CryptoText<string>& a, const CryptoText<string>& b) {
            return a.evaluation < b.evaluation;
    });
    
    return bestResult.text;
}

int main() {
    std::vector<std::string> lines = readFileLines("./data/6.txt");
    std::string input = std::accumulate(lines.begin(), lines.end(), std::string(""));
    input = hexToBin(base64ToHex(input));

    std::cout << break_repeating_key_xor(input) << '\n';

    return 0;
}
