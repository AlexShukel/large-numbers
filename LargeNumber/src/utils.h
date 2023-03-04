//
// Created by alexs on 2023-03-04.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <cinttypes>
#include <string>
#include <algorithm>

inline uint8_t charToDigit(char character) {
    return character - 48;
}

inline char digitToChar(uint8_t digit) {
    return digit + 48;
}

inline bool isZero(const std::string &number) {
    return std::all_of(number.begin(), number.end(), [](char c) { return c == '0'; });
}

#endif //ND1_UTILS_H
