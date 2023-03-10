//
// Created by alexs on 2023-02-19.
//

#include "LargeInt.h"
#include "LargeIntMath.h"
#include "../utils.h"

template<class T>
LargeInt<T>::LargeInt(const std::string &number): math(LargeIntMath<T>(number)) {}

template<class T>
LargeInt<T> &LargeInt<T>::operator=(const LargeInt<T> &other) {
    if (&other != this) {
        // TODO: copy by reference instead of value
        math = other.math;
    }

    return *this;
}

template<class T>
LargeInt<T> LargeInt<T>::operator+(const LargeInt<T> &other) {
    LargeInt<T> copy = *this;
    copy.math.add(other.math);
    return copy;
}

template<class T>
LargeInt<T> LargeInt<T>::operator+() {
    LargeInt<T> copy = *this;
    copy.math.positivate();
    return copy;
}

template<class T>
LargeInt<T> &LargeInt<T>::operator+=(const LargeInt<T> &other) {
    this->math.add(other.math);
    return *this;
}

template<class T>
LargeInt<T> &LargeInt<T>::operator++() {
    math.add(LargeIntMath<T>(1));
    return *this;
}

template<class T>
const LargeInt<T> LargeInt<T>::operator++(int) {
    LargeInt<T> temp = *this;
    ++(*this);
    return temp;
}

template<class T>
LargeInt<T> LargeInt<T>::operator-(const LargeInt<T> &other) const {
    LargeInt<T> copy = *this;
    copy -= other;
    return copy;
}

template<class T>
LargeInt<T> LargeInt<T>::operator-() const {
    LargeInt<T> copy = *this;
    copy.math.negate();
    return copy;
}

template<class T>
LargeInt<T> &LargeInt<T>::operator-=(const LargeInt<T> &other) {
    math.subtract(other.math);
    return *this;
}

template<class T>
LargeInt<T> &LargeInt<T>::operator--() {
    math.subtract(LargeIntMath<T>(1));
    return *this;
}

template<class T>
const LargeInt<T> LargeInt<T>::operator--(int) {
    LargeInt<T> temp = *this;
    --(*this);
    return temp;
}

template<class T>
LargeInt<T> LargeInt<T>::operator*(const LargeInt<T> &other) {
    LargeInt<T> copy = *this;
    copy.math.multiply(other.math);
    return copy;
}

template<class T>
LargeInt<T> &LargeInt<T>::operator*=(const LargeInt<T> &other) {
    this->math.multiply(other.math);
    return *this;
}

template<class T>
bool LargeInt<T>::operator==(const LargeInt<T> &other) const {
    return this->math.compare(other.math) == 0;
}

template<class T>
bool LargeInt<T>::operator!=(const LargeInt<T> &other) const {
    return this->math.compare(other.math) != 0;
}

template<class T>
bool LargeInt<T>::operator<(const LargeInt<T> &other) const {
    return this->math.compare(other.math) < 0;
}

template<class T>
bool LargeInt<T>::operator>(const LargeInt<T> &other) const {
    return this->math.compare(other.math) > 0;
}

template<class T>
bool LargeInt<T>::operator<=(const LargeInt<T> &other) const {
    return this->math.compare(other.math) <= 0;
}

template<class T>
bool LargeInt<T>::operator>=(const LargeInt<T> &other) const {
    return this->math.compare(other.math) >= 0;
}

template<class T>
std::string LargeInt<T>::toString() const {
    return math.toString();
}

template
class LargeInt<uint8_t>;

template
class LargeInt<uint32_t>;
