//
// Created by alexs on 2023-02-26.
//

#include "LargeIntMath.h"

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
    bool isThisLonger = this->coefficients.size() >= addend.coefficients.size();
    int maxSize = isThisLonger ? this->coefficients.size() : addend.coefficients.size();
    int thisInitialSize = this->coefficients.size();
    bool carry = false;

    if (!isThisLonger) {
        this->coefficients.resize(maxSize);
    }

    for (int i = 0; i < maxSize; ++i) {
        T firstMember = i < thisInitialSize ? this->coefficients[i] : 0;
        T secondMember = i < addend.coefficients.size() ? addend.coefficients[i] : 0;

        T sum = firstMember + secondMember;

        if (carry) {
            sum += 1;
        }

        carry = (firstMember > sum) || (secondMember > sum) ||
                (carry && (firstMember == sum || secondMember == sum));

        if (carry) {
            this->coefficients[i] = sum - pow(2, sizeof(T) * 8);
        } else {
            this->coefficients[i] = sum;
        }
    }

    if (carry) {
        this->coefficients.push_back(carry);
    }
}

template
class LargeIntMath<uint8_t>;

template
class LargeIntMath<uint32_t>;
