//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>

bool isZero(const std::string &number);

std::string getBinary(std::string number);

template<typename T>
void getNumberCoefficients(std::vector<T> &coefficients, const std::string &binary) {
    int power = 1, temp = 0;

    int i = 0;
    for (auto it = binary.rbegin(); it != binary.rend(); ++it) {
        if (i % 8 == 0 && i != 0) {
            coefficients.push_back(temp);
            power = 1;
            temp = 0;
        }

        uint8_t current = *it - 48;
        temp += current * power;

        power *= 2;
        ++i;
    }

    if (temp > 0) {
        coefficients.push_back(temp);
    }

    if (coefficients.empty()) {
        coefficients.push_back(0);
    }
}

#endif //ND1_UTILS_H
