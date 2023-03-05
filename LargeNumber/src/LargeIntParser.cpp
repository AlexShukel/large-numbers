//
// Created by alexs on 2023-03-04.
//

#include "LargeIntParser.h"
#include "utils.h"
#include <regex>
#include <bitset>
#include <limits>

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

template<class T>
void LargeIntParser<T>::toTwosComplement(std::vector<T> &coefficients) {
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
void LargeIntParser<T>::coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients) {
    binary.resize(coefficients.size() * COEFFICIENT_BIT_SIZE);
    int index = binary.size() - COEFFICIENT_BIT_SIZE;

    for (T c: coefficients) {
        std::bitset<COEFFICIENT_BIT_SIZE> coefficient = c;

        coefficient.to_string().copy(&binary[index], COEFFICIENT_BIT_SIZE);

        index -= COEFFICIENT_BIT_SIZE;
    }
}

template<class T>
std::string LargeIntParser<T>::toString(std::vector<T> coefficients, bool sign) {
    std::string decimal;

    if (coefficients.empty()) {
        coefficients.push_back(sign ? std::numeric_limits<T>::max() : 0);
    }

    if (sign) {
        toTwosComplement(coefficients);
    }

    std::string binary;
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

    return decimal;
}

template<class T>
void LargeIntParser<T>::fromString(std::vector<T> &coefficients, bool &sign, const std::string &number) {
    if (!std::regex_match(number, std::regex("^-?\\d+$"))) {
        throw std::invalid_argument("LargeInt validation error: number does not match regex format \"^-?\\d+$\"");
    }

    sign = number[0] == '-';
    std::string normalizedDecimal = number.substr(sign);

    if (isZero(normalizedDecimal)) {
        sign = false;
    }

    std::bitset<COEFFICIENT_BIT_SIZE> coefficient = 0;
    int coefficientSize = 0;

    while (!isZero(normalizedDecimal)) {
        coefficient >>= 1;
        coefficient[COEFFICIENT_BIT_SIZE - 1] = charToDigit(normalizedDecimal[normalizedDecimal.size() - 1]) % 2;
        ++coefficientSize;

        if (coefficientSize == COEFFICIENT_BIT_SIZE) {
            coefficients.push_back(coefficient.to_ulong());
            coefficient.reset();
            coefficientSize = 0;
        }

        int nextAdditive = 0;
        for (char &character: normalizedDecimal) {
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

    if (coefficientSize > 0) {
        coefficient >>= COEFFICIENT_BIT_SIZE - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }

    if (sign) {
        toTwosComplement(coefficients);
    }
}

template<class T>
void LargeIntParser<T>::fromInteger(std::vector<T> &coefficients, bool &sign, int number) {
    sign = number < 0;

    if (sign) {
        number *= -1;
    }

    int base = std::numeric_limits<T>::max() + 1;
    while (number > 0) {
        coefficients.push_back(number % base);

        number /= base;
    }

    if (coefficients.empty()) {
        coefficients.push_back(0);
    }

    if (sign) {
        toTwosComplement(coefficients);
    }
}

template
class LargeIntParser<uint8_t>;

template
class LargeIntParser<uint32_t>;
