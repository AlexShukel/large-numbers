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

template std::string numberToBinary(uint8_t number);

template std::string numberToBinary(uint32_t number);

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

template void getBinaryFromCoefficients(std::string &binary, const std::vector<uint8_t> &coefficients, bool sign);

template void getBinaryFromCoefficients(std::string &binary, const std::vector<uint32_t> &coefficients, bool sign);

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

template void getCoefficientsFromBinary(std::vector<uint8_t> &coefficients, const std::string &binary, bool sign);

template void getCoefficientsFromBinary(std::vector<uint32_t> &coefficients, const std::string &binary, bool sign);
