//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <cstdint>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>

uint8_t charToDigit(char character);

char digitToChar(uint8_t digit);

bool isZero(const std::string &number);

uint8_t euclideanDivision(std::string &binary);

template<class T>
void toTwosComplement(std::vector<T> &coefficients) {
    T carry = 1;

    for (auto &c: coefficients) {
        c = ~c;

        T prevC = c;
        c += carry;

        if (c > prevC) {
            carry = 0;
        }
    }
}

#endif //ND1_UTILS_H
