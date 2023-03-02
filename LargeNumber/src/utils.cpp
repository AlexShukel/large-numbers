//
// Created by alexs on 2023-02-26.
//

#include "utils.h"
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>

using std::string;
using std::vector;
using std::bitset;

uint8_t charToDigit(char character) {
    return character - 48;
}

char digitToChar(uint8_t digit) {
    return digit + 48;
}

bool isZero(const string &number) {
    uint8_t padding = !number.empty() && number[0] == '-' ? 1 : 0;
    return std::all_of(number.begin() + padding, number.end(), [](char c) { return c == '0'; });
}

template<class T>
void toTwosComplement(vector<T> &coefficients) {
    uint8_t carry = 1;

    for (auto &c: coefficients) {
        c = ~c;

        uint8_t prevC = c;
        c += carry;

        if (c > prevC) {
            carry = 0;
        }
    }
}

template void toTwosComplement(vector<uint8_t> &coefficients);

template void toTwosComplement(vector<uint32_t> &coefficients);

template<class T>
void getCoefficients(vector<T> &coefficients, string &decimal, bool sign) {
    constexpr int byteSize = sizeof(T) * 8;
    bitset<byteSize> coefficient = 0;
    int coefficientSize = 0;

    while (!isZero(decimal)) {
        coefficient >>= 1;
        coefficient[byteSize - 1] = charToDigit(decimal[decimal.size() - 1]) % 2;
        ++coefficientSize;

        if (coefficientSize == byteSize) {
            coefficients.push_back(coefficient.to_ulong());
            coefficient.reset();
            coefficientSize = 0;
        }

        int nextAdditive = 0;
        for (char &character: decimal) {
            int additive = nextAdditive;
            uint8_t digit = charToDigit(character);

            if (digit % 2 == 1) {
                nextAdditive = 5;
            } else {
                nextAdditive = 0;
            }

            character = digitToChar(digit / 2 + additive);
        }
    }

    if (coefficientSize > 0 || coefficients.empty()) {
        coefficient >>= byteSize - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }

    if (sign) {
        toTwosComplement(coefficients);
    }
}

template void getCoefficients(vector<uint8_t> &coefficients, string &decimal, bool sign);

template void getCoefficients(vector<uint32_t> &coefficients, string &decimal, bool sign);

uint8_t euclideanDivision(string &binary) {
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

template<class T>
void coefficientsToBinary(string &binary, const vector<T> &coefficients) {
    constexpr int byteSize = sizeof(T) * 8;
    binary.resize(coefficients.size() * byteSize);
    int index = binary.size() - byteSize;

    for (T c: coefficients) {
        bitset<byteSize> coefficient = c;

        coefficient.to_string().copy(&binary[index], byteSize);

        index -= byteSize;
    }
}

template void coefficientsToBinary(string &binary, const vector<uint8_t> &coefficients);

template void coefficientsToBinary(string &binary, const vector<uint32_t> &coefficients);

template<class T>
void getDecimal(string &decimal, vector<T> coefficients, bool sign) {
    if (sign) {
        toTwosComplement(coefficients);
    }

    string binary;
    coefficientsToBinary(binary, coefficients);

    while (!isZero(binary)) {
        uint8_t remainder = euclideanDivision(binary);
        decimal.push_back(digitToChar(remainder));
    }

    if (decimal.empty()) {
        decimal.push_back('0');
    } else if (sign) {
        decimal.push_back('-');
    }

    std::reverse(decimal.begin(), decimal.end());
}

template void getDecimal(string &decimal, const vector<uint8_t> coefficients, bool sign);

template void getDecimal(string &decimal, const vector<uint32_t> coefficients, bool sign);

template<class T>
void integerToCoefficients(std::vector<T> &coefficients, int number) {
    int size = static_cast<int>(pow(2, sizeof(T) * 8));

    while (number > 0) {
        coefficients.push_back(number % size);

        number /= size;
    }

    if (coefficients.empty()) {
        coefficients.push_back(0);
    }
}

template void integerToCoefficients(std::vector<uint8_t> &coefficients, int number);

template void integerToCoefficients(std::vector<uint32_t> &coefficients, int number);
