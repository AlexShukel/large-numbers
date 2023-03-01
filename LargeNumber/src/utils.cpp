//
// Created by alexs on 2023-02-26.
//

#include "utils.h"
#include <algorithm>
#include <vector>

using std::string;
using std::vector;

bool isZero(const string &number) {
    uint8_t padding = !number.empty() && number[0] == '-' ? 1 : 0;
    return std::all_of(number.begin() + padding, number.end(), [](char c) { return c == '0'; });
}

string getBinary(string decimal) {
    string result;

    while (!isZero(decimal)) {
        if ((decimal[decimal.size() - 1] - 48) % 2 == 1) {
            result.push_back('1');
        } else {
            result.push_back('0');
        }

        int nextAdditive = 0;
        for (char &character: decimal) {
            char x = character;
            int additive = nextAdditive;
            uint8_t digit = x - 48;

            if (digit % 2 == 1) {
                nextAdditive = 5;
            } else {
                nextAdditive = 0;
            }

            character = (char) (digit / 2 + additive + 48);
        }
    }

    std::reverse(result.begin(), result.end());

    if (result.empty()) {
        result.push_back('0');
    }

    return result;
}

uint8_t euclideanDivision(string &binary) {
    uint8_t R = 0;

    for (char &character: binary) {
        uint8_t digit = character - 48;
        R = 2 * R + digit;
        if (R >= 10) {
            character = '1';
            R -= 10;
        } else {
            character = '0';
        }
    }

    return R;
}

string getDecimal(string binary, bool sign) {
    string result;

    while (!isZero(binary)) {
        uint8_t R = euclideanDivision(binary);
        result.push_back((char) (R + 48));
    }

    if (result.empty()) {
        result.push_back('0');
    }

    if (sign) {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());

    return result;
}
