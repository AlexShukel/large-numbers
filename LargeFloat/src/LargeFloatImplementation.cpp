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

        auto integral = LargeIntImplementation<T>(integralSource);
        std::vector<T> fractionCoefficients = getFractionSourceCoefficients(fractionSource);

        // The number is zero
        if (integral.isZero() && fractionCoefficients.empty()) {
            mantissa.coefficients.push_back(0);
            return;
        }

        mantissa.coefficients.resize(integral.coefficients.size() + fractionCoefficients.size());
        std::copy(fractionCoefficients.begin(), fractionCoefficients.end(), mantissa.coefficients.begin());
        std::copy(integral.coefficients.begin(), integral.coefficients.end(),
                  mantissa.coefficients.begin() + fractionCoefficients.size());

        if (integral.isZero()) {
            size_t trimmedZeros = trimBack(mantissa.coefficients, 0);
            exponent -= static_cast<exponent_type>(trimmedZeros);
        } else {
            exponent = static_cast<exponent_type>(integral.coefficients.size() - 1);
        }

        if (fractionCoefficients.empty()) {
            trimFront(mantissa.coefficients, 0);
        }

        if (mantissa.coefficients.empty()) {
            mantissa.coefficients.push_back(0);
        }

        if (sign) {
            mantissa.negate();
        }
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

        // Reverse coefficients as we store LSD -> MSD
        std::reverse(coefficients.begin(), coefficients.end());

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

        size_t thresholdSize = fraction.coefficients.size() + 1;
        if (exponent < 0) {
            thresholdSize += static_cast<size_t>(-exponent) - 1;
        }

        while (!areCoefficientsEmpty(fraction.coefficients) && currentPrecision <= DECIMAL_PRECISION) {
            fraction.multiply(ten);

            if (fraction.coefficients.size() >= thresholdSize) {
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

        // Integral part is 0
        if (exponent < 0) {
            fractionalCoefficients.resize(size);
            std::copy(begin, end,
                      fractionalCoefficients.begin());
            integralCoefficients.push_back(0);
            return;
        }

        // Fractional part is 0
        if (size <= static_cast<size_t>(exponent) + 1) {
            integralCoefficients.resize(size);
            std::copy(begin, end, integralCoefficients.begin());

            if (static_cast<size_t>(exponent) + 1 > size) {
                size_t diff = exponent + 1 - size;
                integralCoefficients.insert(integralCoefficients.begin(), diff, 0);
            }
            return;
        }

        integralCoefficients.resize(exponent + 1);
        size_t fractionalCoefficientsSize = size - exponent - 1;
        fractionalCoefficients.resize(fractionalCoefficientsSize);

        std::copy(begin, begin + fractionalCoefficientsSize, fractionalCoefficients.begin());
        std::copy(begin + fractionalCoefficientsSize, end, integralCoefficients.begin());
    }

    // For debugging
    template
    class LargeFloatImplementation<uint8_t>;

    // For final result
    template
    class LargeFloatImplementation<uint32_t>;
}
