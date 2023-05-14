//
// Created by alexs on 2023-03-04.
//

#include "LargeDoubleParser.h"
#include "LargeIntParser.h"
#include "utils.h"
#include <regex>
#include <bitset>
#include <algorithm>

template<class T>
void LargeDoubleParser<T>::getFractionCoefficients(std::vector<T> &coefficients, std::string fraction) {
    int currentPrecision = 0;

    std::bitset<COEFFICIENT_BIT_SIZE> coefficient = 0;
    int coefficientSize = 0;

    while (currentPrecision < PRECISION && !isZero(fraction)) {
        bool carry = false;
        for (auto it = fraction.rbegin(); it != fraction.rend(); ++it) {
            uint8_t digit = charToDigit(*it) * 2 + carry;
            carry = digit >= 10;
            *it = digitToChar(digit % 10);
        }

        coefficient <<= 1;
        coefficient[0] = carry;
        ++coefficientSize;

        if (coefficientSize == COEFFICIENT_BIT_SIZE) {
            coefficients.push_back(coefficient.to_ulong());

            coefficientSize = 0;
            coefficient.reset();
            ++currentPrecision;
        }
    }

    if (coefficientSize > 0) {
        coefficient <<= COEFFICIENT_BIT_SIZE - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }
}

template<class T>
LargeDoubleMath<T> LargeDoubleParser<T>::fromString(std::string source) {
    std::regex largeDoubleRegex(R"(^-?\d+\.\d+$)");

    if (!std::regex_match(source, largeDoubleRegex)) {
        throw std::invalid_argument("LargeDouble does not math regex!");
    }

    LargeIntMath<T> mantissa;
    exponent_type exponent;
    bool sign = source[0] == '-';

    if (sign) {
        source.erase(source.begin());
    }

    size_t pointIndex = source.find('.');

    std::string integralSource = source.substr(0, pointIndex);
    std::string fractionSource = source.substr(pointIndex + 1);

    bool ignoreSign;
    std::vector<T> integralSourceCoefficients;
    LargeIntParser<T>::fromString(integralSourceCoefficients, ignoreSign, integralSource);

    if (integralSourceCoefficients.empty()) {
        integralSourceCoefficients.push_back(0);
    }

    exponent = integralSourceCoefficients.size();

    std::vector<T> fractionSourceCoefficients;
    getFractionCoefficients(fractionSourceCoefficients, fractionSource);

    if (fractionSourceCoefficients.empty()) {
        fractionSourceCoefficients.push_back(0);
    }

    std::vector<T> &coefficients = mantissa.getCoefficients();
    coefficients.resize(integralSourceCoefficients.size() + fractionSourceCoefficients.size());

    // Concatenate fractional and integral parts coefficients
    int i = 0;
    for (auto it = fractionSourceCoefficients.rbegin(); it != fractionSourceCoefficients.rend(); ++it) {
        coefficients[i] = *it;
        ++i;
    }

    for (auto it = integralSourceCoefficients.begin(); it != integralSourceCoefficients.end(); ++it) {
        coefficients[i] = *it;
        ++i;
    }

    if (sign) {
        mantissa.negate();
    }

    auto result = LargeDoubleMath<T>(mantissa, exponent);

    result.normalize();

    return result;
}

template<class T>
std::string LargeDoubleParser<T>::toString(LargeDoubleMath<T> number) {
    std::string result;

    bool sign = number.getSign();
    if (number.getSign()) {
        number.getMantissa().negate();
    }

    std::vector<T> fractionalCoefficients = number.getFractionalCoefficients();
    std::vector<T> integralCoefficients = number.getIntegralCoefficients();

    LargeIntMath<T> fraction(fractionalCoefficients, false);
    LargeIntMath<T> integral(integralCoefficients, false);
    LargeIntMath<T> ten({10}, false);

    if (sign) {
        result += '-';
    }
    result += integral.toString();
    result += ".";

    size_t fractionWidth = fractionalCoefficients.size();
    while (!areCoefficientsEmpty(fraction.getCoefficients()) && result.length() <= DECIMAL_PRECISION + 2) {
        fraction.multiply(ten);

        if (fraction.getCoefficients().size() > fractionWidth) {
            T value = fraction.getCoefficients().back();
            fraction.getCoefficients().pop_back();
            result += '0' + value;
        } else {
            result += '0';
        }
    }

    if (result.length() > DECIMAL_PRECISION + 1) {
        char last = result.back();
        result.pop_back();

        if (last >= '5') {
            for (auto it = result.rbegin(); it != result.rend(); ++it) {
                *it += 1;
                if (*it > '9') {
                    *it = '0';
                } else {
                    break;
                }
            }
            trimBack(result, '0');
        }
    }

    if (result.back() == '.') {
        result += '0';
    }

    return result;
}

template<class T>
size_t LargeDoubleParser<T>::getPrecision() {
    return PRECISION;
}

template
class LargeDoubleParser<uint8_t>;

template
class LargeDoubleParser<uint32_t>;