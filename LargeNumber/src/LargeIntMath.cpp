//
// Created by alexs on 2023-02-26.
//

#include "LargeIntMath.h"
#include <limits>
#include <bitset>

template<class T>
LargeIntMath<T>::LargeIntMath() {
    sign = false;
    coefficients.push_back(0);
}

template<class T>
LargeIntMath<T>::LargeIntMath(std::vector<T> coefficients, bool sign): coefficients(std::move(coefficients)),
                                                                       sign(sign) {}

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
}

template<class T>
inline T LargeIntMath<T>::getSupplementDigit() const {
    return sign ? std::numeric_limits<T>::max() : 0;
}

template
class LargeIntMath<uint8_t>;

template
class LargeIntMath<uint32_t>;
