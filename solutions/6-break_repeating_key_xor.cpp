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

    // local struct to hold the key size and the average hamming distance
    struct KeySizeWithDistance {
        size_t keySize;
        double averageEditDistance;
    };
    
    // compute the Hamming distance for all key sizes between 2 and 40
    // utilizing the first four blocks of the string
    // and taking the average of the hamming distances
    vector<KeySizeWithDistance> editDistances;
    for (size_t keySize = 2; keySize < 41; keySize++) {
        double sum = 0.0;
        for (int i = 0; i < 4; i++) {
            string block = binString.substr(8 * i * keySize, 8 * keySize);
            string nextBlock = binString.substr(8 * (i + 1) * keySize, 8 * keySize);
            
            sum += hammingDistance(block, nextBlock) / (keySize * 4.0);
        }

        editDistances.push_back({ keySize, sum });
    }
    
    vector<KeySizeWithDistance> lowestEditDistanceKeySizes(3);
    // take the 3 lowest edit distances
    std::partial_sort_copy(
        editDistances.begin(),
        editDistances.end(),
        lowestEditDistanceKeySizes.begin(),
        lowestEditDistanceKeySizes.end(),
        [](const KeySizeWithDistance& a, const KeySizeWithDistance& b) {
            return a.averageEditDistance < b.averageEditDistance;
    });

    vector<string> keysUsed;
    // for each one of the best key sizes
    for (auto [keySize, editDistance] : lowestEditDistanceKeySizes) {
        vector<vector<string>> blocks(
            std::ceil(binString.length() / (float)keySize), vector<string>(keySize)
        );

        // split the string into blocks of size keySize
        for (size_t i = 0; i < binString.length(); i += 8 * keySize) {
            for (size_t j = 0; j < 8 * keySize; j += 8) {
                if (i + j >= binString.length()) {
                    break;
                }
                blocks[i / (8 * keySize)][j / 8] = binString.substr(i + j, 8);
            }
        }

        // transpose the blocks to xor them with the same key
        vector<vector<string>> transposedBlocks = transposeMatrix(blocks);

        string keyUsed;
        for (auto block : transposedBlocks) {
            string blockString = std::accumulate(block.begin(), block.end(), string(""));
            CryptoText<unsigned char> bestCandidate = decrypt_message(blockString);
            // each key here is a byte of the key used to encrypt the original message
            keyUsed += bestCandidate.key;
        }

        keysUsed.push_back(keyUsed);
    }
    
    // for each key candidate, decrypt the message and evaluate it
    vector<CryptoText<string>> results;
    for (auto key : keysUsed) {
        string text = binToASCII(repeating_key_xor(binString, key));
        double score = evaluateText(text);
        results.push_back({ text, key, score });
    }

    // get the best result
    CryptoText<string> bestResult = *std::min_element(results.begin(), results.end(),
        [](const CryptoText<string>& a, const CryptoText<string>& b) {
            return a.evaluation < b.evaluation;
    });
    
    return bestResult.text;
}

int main() {
    std::vector<std::string> lines = readFileLines("./data/6.txt");
    std::string input = std::accumulate(lines.begin(), lines.end(), std::string(""));

    std::cout << break_repeating_key_xor(base64ToBin(input)) << '\n';

    return 0;
}
