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
constexpr size_t LargeDoubleMath<T>::getCurrentBase() {
    return std::bitset<COEFFICIENT_BIT_SIZE>(0).flip().to_ulong() + 1;
}

template<class T>
void LargeDoubleMath<T>::setExponent(exponent_type newExponent) {
    exponent = newExponent;
}

template<class T>
void LargeDoubleMath<T>::setMantissa(LargeIntMath<T> newMantissa) {
    mantissa = newMantissa;
}

template<class T>
void LargeDoubleMath<T>::multiply(const LargeDoubleMath<T> &multiplier) {
    exponent = exponent + multiplier.exponent - getFractionalPartSize() - multiplier.getFractionalPartSize();
    mantissa.multiply(multiplier.mantissa);
    exponent += getFractionalPartSize();
    normalize();
}

template<class T>
void LargeDoubleMath<T>::add(LargeDoubleMath<T> addend) {
    exponent_type E1 = exponent - getFractionalPartSize();
    exponent_type E2 = addend.exponent - addend.getFractionalPartSize();
    size_t diff = getAbsoluteDelta(E1, E2);

    if (E1 > E2) {
        this->mantissa.shiftLeft(diff);
        this->mantissa.add(addend.mantissa);

        this->exponent = E2 + getFractionalPartSize();

        normalize();
    } else {
        addend.mantissa.shiftLeft(diff);
        addend.mantissa.add(this->mantissa);

        addend.exponent = E1 + addend.getFractionalPartSize();

        addend.normalize();
        *this = addend;
    }

//    exponent_type finalExponent = std::max(exponent, addend.exponent);
//
//    bool isThisNegative = mantissa.getSign();
//    bool isAddendNegative = addend.mantissa.getSign();
//
//    if (isThisNegative) {
//        mantissa.negate();
//    }
//
//    if (isAddendNegative) {
//        addend.mantissa.negate();
//    }
//
//    extendFront(mantissa.getCoefficients(), (T) 0, getAbsoluteDelta(exponent, finalExponent));
//    extendFront(mantissa.getCoefficients(), (T) 0, getAbsoluteDelta(addend.exponent, finalExponent));
//
//    size_t width = std::max(mantissa.getCoefficients().size(), addend.mantissa.getCoefficients().size());
//
//    extendBack(mantissa.getCoefficients(), (T) 0, getAbsoluteDelta(width, mantissa.getCoefficients().size()));
//    extendBack(addend.mantissa.getCoefficients(), (T) 0,
//               getAbsoluteDelta(width, addend.mantissa.getCoefficients().size()));
//
//    if (isThisNegative) {
//        mantissa.negate();
//    }
//
//    if (isAddendNegative) {
//        addend.mantissa.negate();
//    }
//
//    mantissa.add(addend.mantissa);
//    finalExponent += mantissa.getCoefficients().size() - width;
//
//    width = mantissa.getCoefficients().size();
//    normalize();
//    finalExponent -= width - mantissa.getCoefficients().size();
//    trimBack(mantissa.getCoefficients(), mantissa.getSupplementDigit());
//
//    if (mantissa.getCoefficients().empty()) {
//        exponent = 1;
//    } else {
//        exponent = finalExponent;
//    }
}

template
class LargeDoubleMath<uint8_t>;

template
class LargeDoubleMath<uint32_t>;
