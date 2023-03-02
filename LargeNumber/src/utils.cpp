//
// Created by alexs on 2023-02-26.
//

#include "utils.h"
#include <algorithm>
#include <vector>
#include <bitset>

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
