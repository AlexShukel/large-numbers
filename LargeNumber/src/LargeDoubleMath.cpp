//
// Created by alexs on 2023-03-03.
//

#include "LargeDoubleMath.h"
#include "utils.h"
#include "LargeDoubleParser.h"
#include <regex>

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(): mantissa(LargeIntMath<T>()), exponent(0) {}

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(LargeIntMath<T> mantissa, exponent_type exponent): mantissa(std::move(mantissa)),
                                                                                       exponent(exponent) {}

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(
        LargeIntMath<T> mantissa): mantissa(std::move(mantissa)), exponent(mantissa.getCoefficients().size()) {
    this->normalize();
}

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(const std::string &number) {
    if (!std::regex_match(number, std::regex("^-?\\d+\\.\\d+$"))) {
        throw std::invalid_argument("LargeDouble validation error: number does not match format (<digits>.<digits>).");
    }

    *this = LargeDoubleParser<T>::parse(number);
}

template<class T>
bool &LargeDoubleMath<T>::getSign() {
    return mantissa.getSign();
}

template<class T>
bool LargeDoubleMath<T>::getSign() const {
    return mantissa.getSign();
}

template<class T>
exponent_type &LargeDoubleMath<T>::getExponent() {
    return exponent;
}

template<class T>
exponent_type LargeDoubleMath<T>::getExponent() const {
    return exponent;
}

template<class T>
LargeIntMath<T> &LargeDoubleMath<T>::getMantissa() {
    return mantissa;
}

template<class T>
LargeIntMath<T> LargeDoubleMath<T>::getMantissa() const {
    return mantissa;
}

template<class T>
void LargeDoubleMath<T>::normalize() {
    std::vector<T> &coefficients = mantissa.getCoefficients();
    size_t trimmedFront = trimFront(coefficients, (T) 0);
    exponent -= trimBack(coefficients, mantissa.getSign() ? mantissa.getMaxValue() : (T) 0);

    if (coefficients.empty()) {
        exponent = 1;
    }
}

template<class T>
size_t LargeDoubleMath<T>::getFractionalPartSize() const {
    return std::max(static_cast<size_t>(1), mantissa.getCoefficients().size());
}

template<class T>
void LargeDoubleMath<T>::multiply(const LargeDoubleMath<T> &multiplier) {
    exponent = exponent + multiplier.exponent - getFractionalPartSize() - multiplier.getFractionalPartSize();
    mantissa.multiply(multiplier.mantissa);
    exponent += getFractionalPartSize();
    normalize();
}

template
class LargeDoubleMath<uint8_t>;

template
class LargeDoubleMath<uint32_t>;
