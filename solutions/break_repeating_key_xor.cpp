#include <iostream>
#include <string>
#include "utilities.h"


int main() {
    std::string input = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    std::string base64String = base64ToHex(input);
    std::cout << base64String << '\n';

    return 0;
}
