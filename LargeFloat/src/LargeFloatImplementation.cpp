//
// Created by alexs on 2023-05-16.
//

#include "LargeFloatImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>
#include <cctype>

namespace LargeNumbers {
    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(): mantissa(LargeIntImplementation<T>()), exponent(0) {}

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(const LargeFloatImplementation<T> &other): mantissa(
            other.mantissa), exponent(other.exponent) {}

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(std::string number) {
        if (!std::regex_match(number, std::regex(R"(^-?\d+\.\d+$)"))) {
            throw std::invalid_argument(
                    "LargeFloat validation error: number does not match format (<digits>.<digits>).");
        }

        bool sign = number[0] == '-';
        exponent = 0;

        if (sign) {
            number.erase(number.begin());
        }

        size_t pointIndex = number.find('.');

        std::string integralSource = number.substr(0, pointIndex);
        std::string fractionSource = number.substr(pointIndex + 1);

        auto integral = LargeIntImplementation<T>(integralSource); // LSD -> MSD
        std::vector<T> fractionCoefficients = getFractionSourceCoefficients(fractionSource); // MSD -> LSD

        mantissa.coefficients.resize(fractionCoefficients.size() + integral.coefficients.size());
        std::copy(fractionCoefficients.rbegin(), fractionCoefficients.rend(), mantissa.coefficients.begin());
        std::copy(integral.coefficients.begin(), integral.coefficients.end(),
                  mantissa.coefficients.begin() + fractionCoefficients.size());

        if (!fractionCoefficients.empty()) {
            exponent = -fractionCoefficients.size();
        } else {
            auto trimmed = trimFront(mantissa.coefficients, 0);
            exponent = trimmed;
        }

        if (sign) {
            mantissa.negate();
        }
        mantissa.normalize();
    }

    template<class T>
    std::vector<T> LargeFloatImplementation<T>::getFractionSourceCoefficients(std::string source) const {
        std::vector<T> coefficients;

        size_t currentPrecision = 0;
        // Accumulated current coefficient
        std::bitset<COEFFICIENT_BIT_SIZE> current(0);
        // Index of currently inserted bit
        uint8_t currentIndex = COEFFICIENT_BIT_SIZE;

        while (currentPrecision < PRECISION && !isStringZero(source)) {
            bool carry = false;
            for (auto it = source.rbegin(); it != source.rend(); ++it) {
                uint8_t digit = charToDigit(*it) * 2 + carry;
                carry = digit >= 10;
                *it = digitToChar(digit % 10);
            }

            --currentIndex;
            // Fill in bitset with carry's
            current[currentIndex] = carry;

            // Push the coefficient in vector
            if (currentIndex == 0) {
                coefficients.push_back(static_cast<T>(current.to_ulong()));

                currentIndex = COEFFICIENT_BIT_SIZE;
                current.reset();
                ++currentPrecision;
            }
        }

        // Push the remaining coefficient
        if (currentIndex != COEFFICIENT_BIT_SIZE) {
            coefficients.push_back(static_cast<T>(current.to_ulong()));
        }

        return coefficients;
    }

    template<class T>
    std::string LargeFloatImplementation<T>::toString() const {
        std::string result;

        bool sign = mantissa.sign;
        LargeIntImplementation<T> mantissaCopy = mantissa;

        if (sign) {
            mantissaCopy.negate();
        }

        std::vector<T> integralCoefficients, fractionalCoefficients;
        splitCoefficients(integralCoefficients, fractionalCoefficients, mantissaCopy);

        LargeIntImplementation<T> integral(integralCoefficients, false);
        LargeIntImplementation<T> fraction(fractionalCoefficients, false);
        LargeIntImplementation<T> ten({10}, false);
        LargeIntImplementation<T> one({1}, false);

        if (sign) {
            result += '-';
        }

        size_t currentPrecision = 0;
        std::string fractionalString;

        size_t diff = -exponent > mantissaCopy.coefficients.size() ? (-exponent) - mantissaCopy.coefficients.size() : 0;
        size_t thresholdSize = fraction.coefficients.size() + diff;

        while (!areCoefficientsEmpty(fraction.coefficients) && currentPrecision <= DECIMAL_PRECISION) {
            fraction.multiply(ten);

            if (fraction.coefficients.size() > thresholdSize) {
                fractionalString += digitToChar(static_cast<uint8_t>(fraction.coefficients.back()));
                fraction.coefficients.pop_back();
            } else {
                fractionalString += '0';
            }

            ++currentPrecision;
        }

        // Adjust last digit
        if (currentPrecision > DECIMAL_PRECISION) {
            fraction.multiply(ten);
            T lastDigit = fraction.coefficients.back();
            if (lastDigit >= 5) {
                ++fractionalString[fractionalString.size() - 1];
            }
        }

        bool carry = roundFractionalString(fractionalString);
        if (carry) {
            integral.add(one);
        }

        result += integral.toString();
        result += '.';
        result += fractionalString;

        if (result.back() == '.') {
            result.push_back('0');
        }

        return result;
    }

    template<class T>
    bool LargeFloatImplementation<T>::roundFractionalString(std::string &fraction) const {
        if (fraction.size() > DECIMAL_PRECISION) {
            char last = fraction.back();
            fraction.pop_back();

            bool shouldIncrementIntegral = false;

            if (last >= '5') {
                for (auto it = fraction.rbegin(); it != fraction.rend(); ++it) {
                    ++(*it);

                    if (*it > '9') {
                        *it = '0';
                        shouldIncrementIntegral = true;
                    } else {
                        break;
                    }
                }
            }

            trimBack(fraction, '0');

            if (fraction.size() == 1 && fraction[0] == '0') {
                fraction.clear();
            }

            if (fraction.empty()) {
                return shouldIncrementIntegral;
            }
        }

        return false;
    }

    template<class T>
    void LargeFloatImplementation<T>::splitCoefficients(std::vector<T> &integralCoefficients,
                                                        std::vector<T> &fractionalCoefficients,
                                                        const LargeIntImplementation<T> &mantissaCopy) const {
        size_t size = mantissaCopy.coefficients.size();

        auto begin = mantissaCopy.coefficients.begin();
        auto end = mantissaCopy.coefficients.end();

        // Fractional part is 0
        if (exponent >= 0) {
            integralCoefficients.resize(size);
            std::copy(begin, end, integralCoefficients.begin());
            integralCoefficients.insert(integralCoefficients.begin(), exponent, 0);
            return;
        }

        // Integral part is 0
        if (-exponent >= size) {
            fractionalCoefficients.resize(size);
            std::copy(begin, end,
                      fractionalCoefficients.begin());
            integralCoefficients.push_back(0);
            return;
        }

        // There are both integral and fractional parts

        size_t diff = size - (-exponent);
        fractionalCoefficients.resize(-exponent);
        integralCoefficients.resize(diff);

        std::copy(begin, begin + (-exponent), fractionalCoefficients.begin()); // MSD -> LSD
        std::copy(begin + (-exponent), end, integralCoefficients.begin()); // LSD -> MSD
    }

    template<class T>
    void LargeFloatImplementation<T>::multiply(const LargeFloatImplementation &multiplier) {
        mantissa.multiply(multiplier.mantissa);
        exponent += multiplier.exponent;
        normalize();
    }

    template<class T>
    void LargeFloatImplementation<T>::normalize() {
        mantissa.normalize();
        if (mantissa.isZero()) {
            exponent = 0;
        }
    }

    // For debugging
    template
    class LargeFloatImplementation<uint8_t>;

    // For final result
    template
    class LargeFloatImplementation<uint32_t>;
}
