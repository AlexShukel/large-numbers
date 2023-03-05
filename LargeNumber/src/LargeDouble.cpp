//
// Created by alexs on 2023-03-03.
//

#include "LargeDouble.h"

template<class T>
LargeDouble<T>::LargeDouble(): math(LargeDoubleMath<T>()) {}

template<class T>
LargeDouble<T>::LargeDouble(LargeIntMath<T> mantissa, exponent_type exponent): math(
        LargeDoubleMath<T>(mantissa, exponent)) {}

template<class T>
LargeDouble<T>::LargeDouble(const LargeIntMath<T> &mantissa): math(LargeDoubleMath<T>(mantissa)) {}

template<class T>
LargeDouble<T>::LargeDouble(const std::string &number): math(LargeDoubleMath<T>(number)) {}

template<class T>
LargeDouble<T> LargeDouble<T>::operator*(const LargeDouble<T> &other) {
    LargeDouble<T> copy = *this;
    copy *= other;
    return copy;
}

template<class T>
LargeDouble<T> &LargeDouble<T>::operator*=(const LargeDouble<T> &other) {
    this->math.multiply(other.math);
    return *this;
}

template<class T>
LargeDouble<T> LargeDouble<T>::operator+(const LargeDouble<T> &other) {
    LargeDouble<T> copy = *this;
    copy += other;
    return copy;
}

template<class T>
LargeDouble<T> &LargeDouble<T>::operator+=(const LargeDouble<T> &other) {
    this->math.add(other.math);
    return *this;
}

template
class LargeDouble<uint8_t>;

template
class LargeDouble<uint32_t>;
