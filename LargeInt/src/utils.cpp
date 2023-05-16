//
// Created by alexs on 2023-05-14.
//

#include "utils.h"
#include <vector>

uint8_t charToDigit(char character) {
    return character - 48;
}

char digitToChar(uint8_t digit) {
    return static_cast<char>(digit + 48);
}

bool isStringZero(const std::string &number) {
    return std::all_of(number.begin(), number.end(), [](char c) { return c == '0'; });
}

uint8_t euclideanDivision(std::string &binary) {
    uint8_t remainder = 0;

    for (char &character: binary) {
        uint8_t digit = charToDigit(character);
        remainder = 2 * remainder + digit;
        if (remainder >= 10) {
            character = '1';
            remainder -= 10;
        } else {
            character = '0';
        }
    }

    return remainder;
}
