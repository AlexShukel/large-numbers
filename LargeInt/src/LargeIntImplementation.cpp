//
// Created by alexs on 2023-05-14.
//

#include "LargeIntImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>

namespace LargeNumbers {
    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(): sign(false) {}

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(const std::string &number) {
        if (!std::regex_match(number, std::regex("^-?\\d+$"))) {
            throw std::invalid_argument(R"(LargeInt validation error: number does not match regex format "^-?\d+$")");
        }

        sign = number[0] == '-';
        std::string normalizedDecimal = number.substr(sign);

        if (isZero(normalizedDecimal)) {
            sign = false;
            return;
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
    LargeIntImplementation<T>::LargeIntImplementation(const LargeIntImplementation<T> &other): sign(other.sign),
                                                                                               coefficients(
                                                                                                       other.coefficients) {}

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(const std::vector<T> &coefficients, bool sign): coefficients(
            coefficients), sign(sign) {}

    template<class T>
    void
    LargeIntImplementation<T>::coefficientsToBinary(std::string &binary, const std::vector<T> &coefficientsCopy) const {
        binary.resize(coefficientsCopy.size() * COEFFICIENT_BIT_SIZE);
        int index = binary.size() - COEFFICIENT_BIT_SIZE;

        for (T c: coefficientsCopy) {
            std::bitset<COEFFICIENT_BIT_SIZE> coefficient = c;

            coefficient.to_string().copy(&binary[index], COEFFICIENT_BIT_SIZE);

            index -= COEFFICIENT_BIT_SIZE;
        }
    }

    template<class T>
    std::string LargeIntImplementation<T>::toString() const {
        std::vector<T> coefficientsCopy = coefficients;
        std::string decimal;

        if (coefficients.empty()) {
            coefficientsCopy.push_back(sign ? std::numeric_limits<T>::max() : 0);
        }

        if (sign) {
            toTwosComplement(coefficientsCopy);
        }

        std::string binary;
        coefficientsToBinary(binary, coefficientsCopy);

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

    // For debugging
    template
    class LargeIntImplementation<uint8_t>;

    // For final result
    template
    class LargeIntImplementation<uint32_t>;
}
