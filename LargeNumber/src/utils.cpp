//
// Created by alexs on 2023-03-04.
//

#include "utils.h"
#include <vector>

void decimalStringToNumbers(std::vector<uint8_t> &output, const std::string &source) {
    output.resize(source.size());

    for (int i = 0; i < source.size(); ++i) {
        output[i] = charToDigit(source[i]);
    }
}
