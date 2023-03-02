//
// Created by alexs on 2023-02-26.
//

#include <stdexcept>
#include <limits>
#include <bitset>
#include "LargeIntMath.h"
#include "utils.h"

template<class T>
LargeIntMath<T>::LargeIntMath() {
    sign = false;
    coefficients.push_back(0);
}

// Conversion from readable string to coefficients
template<class T>
LargeIntMath<T>::LargeIntMath(const std::string &number) {
    if (number.empty()) {
        throw std::logic_error("Cannot initialize a LargeInt with empty string.");
    }

    sign = false;
    int from = 0;
    if (number[0] == '-') {
        sign = true;
    }

    if (number[0] == '-' || number[0] == '+') {
        ++from;
    }

    std::string normalizedNumber = number.substr(from);

    getCoefficients(coefficients, normalizedNumber, sign);
}

// Conversion from coefficients to readable string
template<class T>
std::string LargeIntMath<T>::toString() const {
    std::string decimal;
    getDecimal(decimal, coefficients, sign);
    return decimal;
}

template<class T>
void LargeIntMath<T>::add(const LargeIntMath<T> &addend) {
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

    std::bitset<COEFFICIENT_SIZE> additional(getSupplementDigit() + addend.getSupplementDigit() + carry);
    sign = additional[COEFFICIENT_SIZE - 1];

    if (additional != getSupplementDigit()) {
        coefficients.push_back(additional.to_ulong());
    }
}

template<class T>
T LargeIntMath<T>::getSupplementDigit() const {
    return sign ? std::numeric_limits<T>::max() : 0;
}

template
class LargeIntMath<uint8_t>;

template
class LargeIntMath<uint32_t>;
