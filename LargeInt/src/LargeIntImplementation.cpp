//
// Created by alexs on 2023-05-14.
//

#include "LargeIntImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>

namespace LargeNumbers {
    template<class T>
    const T LargeIntImplementation<T>::MAX_COEFFICIENT_VALUE = static_cast<T>(std::bitset<COEFFICIENT_BIT_SIZE>(
            0).flip().to_ulong());

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
                coefficients.push_back(static_cast<T>(coefficient.to_ulong()));
                coefficient.reset();
                coefficientSize = 0;
            }

            uint8_t nextAdditive = 0;
            for (char &character: normalizedDecimal) {
                uint8_t additive = nextAdditive;
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
            coefficients.push_back(static_cast<T>(coefficient.to_ulong()));
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

    template<class T>
    T LargeIntImplementation<T>::getSupplementDigit() const {
        return sign ? std::numeric_limits<T>::max() : 0;
    }

    template<class T>
    void LargeIntImplementation<T>::normalize() {
        trimBack(coefficients, sign ? MAX_COEFFICIENT_VALUE : (T) 0);
    }

    template<class T>
    void LargeIntImplementation<T>::negate() {
        if (coefficients.empty()) {
            return;
        }

        sign = !sign;
        toTwosComplement(coefficients);
    }

    template<class T>
    void LargeIntImplementation<T>::add(const LargeIntImplementation<T> &addend) {
        auto firstIt = coefficients.begin();
        auto secondIt = addend.coefficients.begin();

        T carry = 0;

        while (firstIt != coefficients.end() || secondIt != addend.coefficients.end()) {
            T firstMember = firstIt != coefficients.end() ? *firstIt : getSupplementDigit();
            T secondMember = secondIt != addend.coefficients.end() ? *secondIt : getSupplementDigit();

            T sum = firstMember + secondMember + carry;

            carry = (firstMember > sum) || (secondMember > sum) ||
                    (carry && (firstMember == sum || secondMember == sum));

            if (firstIt != coefficients.end()) {
                *firstIt = sum;
                ++firstIt;
            } else {
                coefficients.push_back(sum);
                firstIt = coefficients.end();
            }

            if (secondIt != addend.coefficients.end()) {
                ++secondIt;
            }
        }

        std::bitset<COEFFICIENT_BIT_SIZE> additional(getSupplementDigit() + addend.getSupplementDigit() + carry);
        sign = additional[COEFFICIENT_BIT_SIZE - 1];

        if (additional != getSupplementDigit()) {
            coefficients.push_back(static_cast<T>(additional.to_ulong()));
        }

        this->normalize();
    }

    template<class T>
    void LargeIntImplementation<T>::subtract(LargeIntImplementation<T> subtrahend) {
        subtrahend.negate();
        this->add(subtrahend);
    }

    // For debugging
    template
    class LargeIntImplementation<uint8_t>;

    // For final result
    template
    class LargeIntImplementation<uint32_t>;
}
