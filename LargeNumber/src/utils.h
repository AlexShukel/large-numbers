//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

bool isZero(const std::string &number);

std::string getBinary(std::string decimal);

std::string getDecimal(std::string binary, bool sign);

template<class T>
std::string numberToBinary(T number) {
    std::string result;

    while (number != 0) {
        result.push_back(number % 2 + 48);

        number /= 2;
    }

    while (result.size() < sizeof(T) * 8) {
        result.push_back('0');
    }

    return result;
}

template<class T>
void getBinaryFromCoefficients(std::string &binary, const std::vector<T> &coefficients, bool sign) {
    if (coefficients.empty()) {
        binary.push_back('0');
        return;
    }

    auto coefficientsCopy = (std::vector<T>) coefficients;
    if (sign) {
        --coefficientsCopy[0];

        for (int i = 0; i < coefficientsCopy.size(); ++i) {
            coefficientsCopy[i] = ~coefficientsCopy[i];
        }
    }

    for (auto c: coefficientsCopy) {
        std::string binaryPart = numberToBinary(c);
        binary.append(binaryPart);
    }

    size_t i = binary.size() - 1;
    while (binary[i] == '0' && !binary.empty()) {
        binary.pop_back();
        --i;
    }

    std::reverse(binary.begin(), binary.end());
}

template<typename T>
void getCoefficientsFromBinary(std::vector<T> &coefficients, const std::string &binary, bool sign) {
    int power = 1, temp = 0;

    int i = 0;
    for (auto it = binary.rbegin(); it != binary.rend(); ++it) {
        if (i % (sizeof(T) * 8) == 0 && i != 0) {
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

    // Invert bits and add one
    if (sign) {
        for (int j = 0; j < coefficients.size(); ++j) {
            coefficients[j] = ~coefficients[j];

            if (j == 0) {
                ++coefficients[j];
            }
        }
    }
}

#endif //ND1_UTILS_H
