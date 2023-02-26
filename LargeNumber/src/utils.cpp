//
// Created by alexs on 2023-02-26.
//

#include "utils.h"
#include <algorithm>
#include <vector>

using std::string;
using std::vector;

bool isZero(const string &number) {
    return std::all_of(number.begin(), number.end(), [](char c) { return c == '0'; });
}

string getBinary(string number) {
    string result;

    while (!isZero(number)) {
        if ((number[number.size() - 1] - 48) % 2 == 1) {
            result.push_back('1');
        } else {
            result.push_back('0');
        }

        int nextAdditive = 0;
        for (int i = 0; i < number.size(); ++i) {
            char x = number[i];
            int additive = nextAdditive;
            uint8_t digit = x - 48;

            if (digit % 2 == 1) {
                nextAdditive = 5;
            } else {
                nextAdditive = 0;
            }

            number[i] = (char) (digit / 2 + additive + 48);
        }
    }

    std::reverse(result.begin(), result.end());

    if (result.empty()) {
        result.push_back('0');
    }

    return result;
}
