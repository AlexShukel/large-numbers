//
// Created by alexs on 2023-02-19.
//

#include <utility>
#include <algorithm>
#include <cmath>
#include "LargeNumber.h"

template<class T>
void LargeNumber<T>::additionImpl(LargeNumber<T> &first, const LargeNumber<T> &second) {
    bool isFirstLonger = first.coefficients.size() >= second.coefficients.size();
    int maxSize = isFirstLonger ? first.coefficients.size() : second.coefficients.size();
    bool carry = false;

    if (!isFirstLonger) {
        first.coefficients.resize(maxSize);
    }

    for (int i = 0; i < maxSize; ++i) {
        T firstMember = i < first.coefficients.size() ? first.coefficients[i] : 0;
        T secondMember = i < second.coefficients.size() ? second.coefficients[i] : 0;

        T sum = firstMember + secondMember;

        if (carry) {
            sum += 1;
        }

        carry = (firstMember > sum) || (secondMember > sum) ||
                (carry && (firstMember == sum || secondMember == sum));

        if (carry) {
            first.coefficients[i] = sum - pow(2, sizeof(T) * 8);
        } else {
            first.coefficients[i] = sum;
        }
    }

    if (carry) {
        first.coefficients.push_back(carry);
    }
}

template<class T>
LargeNumber<T>::LargeNumber(std::vector<T> coefficients, bool sign) : coefficients(std::move(coefficients)),
                                                                      sign(sign) {}

template<class T>
LargeNumber<T> LargeNumber<T>::operator+(const LargeNumber<T> &other) {
    LargeNumber<T> copy = *this;

    additionImpl(copy, other);

    return copy;
}

template
class LargeNumber<uint8_t>;

template
class LargeNumber<uint32_t>;
