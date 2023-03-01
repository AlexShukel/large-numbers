//
// Created by alexs on 2023-02-19.
//

#include "LargeInt.h"
#include "LargeIntMath.h"
#include "utils.h"

LargeNumberInitException::LargeNumberInitException(const std::string &msg) : message(msg) {}

const char *LargeNumberInitException::what() {
    return message.c_str();
}

template<class T>
LargeInt<T>::LargeInt(const std::string &number) {
    if (number.empty()) {
        throw LargeNumberInitException("Number can not be empty.");
    }

    int i = 0;
    bool sign = false;
    if (number[0] == '-') {
        sign = true;
        ++i;
    }

    if (number[0] == '+') {
        sign = false;
        ++i;
    }

    std::string numberCopy = number.substr(i);

    std::string binary = getBinary(numberCopy);

    std::vector<T> coefficients;
    getCoefficientsFromBinary<T>(coefficients, binary, sign);

    math = new LargeIntMath<T>(coefficients, sign);
}

template<class T>
LargeInt<T>::~LargeInt() {
    delete math;
}

template<class T>
LargeInt<T> LargeInt<T>::operator+(const LargeInt<T> &other) {
    LargeInt<T> copy = *this;
    copy.math->add(*other.math);
    return copy;
}

template<class T>
LargeInt<T> LargeInt<T>::operator+=(const LargeInt<T> &other) {
    this->math->add(*other.math);
    return *this;
}

template<class T>
std::string LargeInt<T>::toString() const {
    return math->toString();
}

template
class LargeInt<uint8_t>;

template
class LargeInt<uint32_t>;
