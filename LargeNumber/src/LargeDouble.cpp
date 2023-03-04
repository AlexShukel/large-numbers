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
LargeDouble<T>::LargeDouble(const std::string &number): math(LargeDoubleMath<T>(number)) {}

template
class LargeDouble<uint8_t>;

template
class LargeDouble<uint32_t>;
