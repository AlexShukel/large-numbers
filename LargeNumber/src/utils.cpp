//
// Created by alexs on 2023-02-26.
//

#include "utils.h"
#include <algorithm>
#include <vector>
#include <bitset>
#include <limits>
#include <tuple>

using std::string;
using std::vector;
using std::bitset;

inline uint8_t charToDigit(char character) {
    return character - 48;
}

inline char digitToChar(uint8_t digit) {
    return digit + 48;
}

inline bool isZero(const string &number) {
    uint8_t padding = !number.empty() && number[0] == '-' ? 1 : 0;
    return std::all_of(number.begin() + padding, number.end(), [](char c) { return c == '0'; });
}

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
void LargeIntUtils<T>::coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients) {
    binary.resize(coefficients.size() * COEFFICIENT_BIT_SIZE);
    int index = binary.size() - COEFFICIENT_BIT_SIZE;

    for (T c: coefficients) {
        bitset<COEFFICIENT_BIT_SIZE> coefficient = c;

        coefficient.to_string().copy(&binary[index], COEFFICIENT_BIT_SIZE);

        index -= COEFFICIENT_BIT_SIZE;
    }
}

template<class T>
void LargeIntUtils<T>::toTwosComplement(std::vector<T> &coefficients) {
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

template<class T>
void LargeIntUtils<T>::integerToCoefficients(std::vector<T> &coefficients, int number) {
    // FIXME: what if number is negative
    int base = std::numeric_limits<T>::max() + 1;
    while (number > 0) {
        coefficients.push_back(number % base);

        number /= base;
    }

    if (coefficients.empty()) {
        coefficients.push_back(0);
    }
}

template<class T>
void LargeIntUtils<T>::getDecimal(std::string &decimal, std::vector<T> coefficients, bool sign) {
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

template<class T>
void LargeIntUtils<T>::getCoefficients(std::vector<T> &coefficients, std::string decimal, bool sign) {
    bitset<COEFFICIENT_BIT_SIZE> coefficient = 0;
    int coefficientSize = 0;

    while (!isZero(decimal)) {
        coefficient >>= 1;
        coefficient[COEFFICIENT_BIT_SIZE - 1] = charToDigit(decimal[decimal.size() - 1]) % 2;
        ++coefficientSize;

        if (coefficientSize == COEFFICIENT_BIT_SIZE) {
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
        coefficient >>= COEFFICIENT_BIT_SIZE - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }

    if (sign) {
        toTwosComplement(coefficients);
    }
}

template
class LargeIntUtils<uint8_t>;

template
class LargeIntUtils<uint32_t>;

template<class T>
void LargeDoubleUtils<T>::getFractionCoefficients(std::vector<T> &coefficients, std::string fraction) {
    int currentPrecision = 0;

    bitset<COEFFICIENT_BIT_SIZE> coefficient = 0;
    int coefficientSize = 0;

    while (currentPrecision < PRECISION && !isZero(fraction)) {
        bool carry = false;
        for (auto it = fraction.rbegin(); it != fraction.rend(); ++it) {
            uint8_t digit = charToDigit(*it) * 2 + carry;
            carry = digit >= 10;
            *it = digitToChar(digit % 10);
        }

        coefficient <<= 1;
        coefficient[0] = carry;
        ++coefficientSize;

        if (coefficientSize == COEFFICIENT_BIT_SIZE) {
            coefficients.push_back(coefficient.to_ulong());

            coefficientSize = 0;
            coefficient.reset();
            ++currentPrecision;
        }
    }

    if (coefficientSize > 0 || coefficients.empty()) {
        coefficient <<= COEFFICIENT_BIT_SIZE - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }
}

template<class T>
std::tuple<LargeIntMath<T>, exponent_type, bool> LargeDoubleUtils<T>::parseLargeDouble(const std::string &number) {
    bool sign = number[0] == '-';

    int pointIndex = 0;

    while (number[pointIndex] != '.') {
        ++pointIndex;
    }

    string integralPart = number.substr(0, pointIndex);
    string fractionalPart = number.substr(pointIndex + 1);

    vector<T> integralPartCoefficients;
    vector<T> fractionalPartCoefficients;

    LargeIntUtils<T>::getCoefficients(integralPartCoefficients, integralPart, false);
    getFractionCoefficients(fractionalPartCoefficients, fractionalPart);

    vector<T> finalCoefficients;
    finalCoefficients.resize(integralPartCoefficients.size() + fractionalPartCoefficients.size());

    // Concatenate integral part with fractional
    std::copy(integralPartCoefficients.rbegin(), integralPartCoefficients.rend(), finalCoefficients.begin());
    std::copy(fractionalPartCoefficients.begin(), fractionalPartCoefficients.end(),
              finalCoefficients.begin() + integralPartCoefficients.size());

    if (sign) {
        LargeIntUtils<T>::toTwosComplement(finalCoefficients);
    }

    return {LargeIntMath<T>(finalCoefficients, sign), -fractionalPartCoefficients.size(), sign};
}

template
class LargeDoubleUtils<uint8_t>;

template
class LargeDoubleUtils<uint32_t>;
