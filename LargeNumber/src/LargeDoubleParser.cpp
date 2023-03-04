//
// Created by alexs on 2023-03-04.
//

#include "LargeDoubleParser.h"
#include "LargeIntParser.h"
#include "utils.h"
#include <regex>
#include <bitset>

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

    if (coefficientSize > 0 || coefficients.empty()) {
        coefficient <<= COEFFICIENT_BIT_SIZE - coefficientSize;
        coefficients.push_back(coefficient.to_ulong());
    }
}

template<class T>
void
LargeDoubleParser<T>::fromString(LargeIntMath<T> &mantissa, exponent_type &exponent, bool &sign, std::string number) {
    if (!std::regex_match(number, std::regex("^-?\\d+\\.\\d+$"))) {
        throw std::invalid_argument(
                "LargeDouble validation error: number does not match regex format \"^-?\\d+\\.\\d+$\"");
    }

    sign = number[0] == '-';

    int pointIndex = 0;

    while (number[pointIndex] != '.') {
        ++pointIndex;
    }

    std::string integralPart = number.substr(0, pointIndex);
    std::string fractionalPart = number.substr(pointIndex + 1);

    std::vector<T> integralPartCoefficients;
    std::vector<T> fractionalPartCoefficients;

    bool ignoreSign;
    LargeIntParser<T>::fromString(integralPartCoefficients, ignoreSign, integralPart);
    getFractionCoefficients(fractionalPartCoefficients, fractionalPart);

    std::vector<T> finalCoefficients;
    finalCoefficients.resize(integralPartCoefficients.size() + fractionalPartCoefficients.size());

    // Concatenate integral part with fractional
    std::copy(integralPartCoefficients.rbegin(), integralPartCoefficients.rend(), finalCoefficients.begin());
    std::copy(fractionalPartCoefficients.begin(), fractionalPartCoefficients.end(),
              finalCoefficients.begin() + integralPartCoefficients.size());

    if (sign) {
        LargeIntParser<T>::toTwosComplement(finalCoefficients);
    }

    exponent = -fractionalPartCoefficients.size();
    mantissa = LargeIntMath<T>(finalCoefficients, sign);
}

template<class T>
std::string
LargeDoubleParser<T>::toString(const LargeIntMath<T> &mantissa, const exponent_type &exponent, const bool &sign) {

}

template
class LargeDoubleParser<uint8_t>;

template
class LargeDoubleParser<uint32_t>;
