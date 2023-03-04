//
// Created by alexs on 2023-02-26.
//

#include <stdexcept>
#include <limits>
#include <bitset>
#include "LargeIntMath.h"
#include "LargeIntParser.h"

template<class T>
LargeIntMath<T>::LargeIntMath() {
    sign = false;
    coefficients.push_back(0);
}

// Conversion from readable string to coefficients
template<class T>
LargeIntMath<T>::LargeIntMath(const std::string &number) {
    LargeIntParser<T>::fromString(coefficients, sign, number);
}

template<class T>
LargeIntMath<T>::LargeIntMath(int number) {
    if (number < 0) {
        sign = true;
    } else {
        sign = false;
    }

    LargeIntParser<T>::fromInteger(coefficients, sign, number);
}

template<class T>
LargeIntMath<T>::LargeIntMath(std::vector<T> coefficients, bool sign): coefficients(coefficients), sign(sign) {}

template<class T>
std::vector<T> &LargeIntMath<T>::getCoefficients() {
    return coefficients;
}

template<class T>
std::vector<T> LargeIntMath<T>::getCoefficients() const {
    return coefficients;
}

template<class T>
bool &LargeIntMath<T>::getSign() {
    return sign;
}

template<class T>
bool LargeIntMath<T>::getSign() const {
    return sign;
}

// Conversion from coefficients to readable string
template<class T>
std::string LargeIntMath<T>::toString() const {
    return LargeIntParser<T>::toString(coefficients, sign);
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

    std::bitset<COEFFICIENT_BIT_SIZE> additional(getSupplementDigit() + addend.getSupplementDigit() + carry);
    sign = additional[COEFFICIENT_BIT_SIZE - 1];

    if (additional != getSupplementDigit()) {
        coefficients.push_back(additional.to_ulong());
    }
}

template<class T>
void LargeIntMath<T>::subtract(LargeIntMath<T> subtrahend) {
    subtrahend.negate();
    add(subtrahend);
}

template<class T>
void LargeIntMath<T>::multiply(LargeIntMath<T> multiplier) {
    bool productSign = sign ^ multiplier.sign;

    if (this->sign) {
        this->negate();
    }

    if (multiplier.sign) {
        multiplier.negate();
    }

    LargeIntMath<T> product;

    for (int i = 0; i < multiplier.coefficients.size(); ++i) {
        auto temp = *this;
        temp.multiplyByCoefficient(multiplier.coefficients[i]);
        temp.shiftLeft(i);
        product.add(temp);
    }

    if (productSign) {
        product.negate();
    }

    *this = product;
}

template<class T>
int LargeIntMath<T>::compare(const LargeIntMath<T> &other) const {
    if (sign && !other.sign) {
        return -1;
    }

    if (!sign && other.sign) {
        return 1;
    }

    if (other.coefficients.size() > coefficients.size()) {
        return -1;
    }

    if (coefficients.size() > other.coefficients.size()) {
        return 1;
    }

    // Signs and sized of coefficients are equal now

    for (int i = coefficients.size() - 1; i >= 0; --i) {
        if (coefficients[i] > other.coefficients[i]) {
            return 1;
        }

        if (coefficients[i] < other.coefficients[i]) {
            return -1;
        }
    }

    return 0;
}

template<class T>
void LargeIntMath<T>::negate() {
    LargeIntParser<T>::toTwosComplement(coefficients);
    sign = !sign;
}

template<class T>
void LargeIntMath<T>::positivate() {
    if (sign) {
        sign = false;
        LargeIntParser<T>::toTwosComplement(coefficients);
    }
}

template<class T>
void LargeIntMath<T>::multiplyByCoefficient(T coefficient) {
    T carry = 0;

    int base = std::numeric_limits<T>::max() + 1;
    for (auto &current: coefficients) {
        uint64_t temp = carry + current * coefficient;
        current = temp % base;
        carry = temp / base;
    }

    if (carry > 0) {
        coefficients.push_back(carry);
    }
}

template<class T>
void LargeIntMath<T>::shiftLeft(int shift) {
    coefficients.resize(coefficients.size() + shift);
    for (int i = 0; i < shift; ++i) {
        coefficients.insert(coefficients.begin(), 0);
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
