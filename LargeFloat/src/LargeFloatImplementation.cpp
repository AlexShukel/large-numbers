//
// Created by alexs on 2023-05-16.
//

#include "LargeFloatImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <limits>

#define FLOAT_MAX_DIGITS_COUNT 1024

namespace LargeNumbers {
    template<class T>
    int LargeFloatImplementation<T>::DECIMAL_PRECISION = 100;

    template<class T>
    size_t LargeFloatImplementation<T>::PRECISION =
            static_cast<size_t>(672 / static_cast<double>(COEFFICIENT_BIT_SIZE)) + 1;

    template<class T>
    LargeFloatImplementation<T> LargeFloatImplementation<T>::EPSILON
            = LargeFloatImplementation<T>(
                    "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

    template<class T>
    void LargeFloatImplementation<T>::setDecimalPrecision(int precision) {
        DECIMAL_PRECISION = precision;
        PRECISION = static_cast<size_t>((static_cast<size_t>((precision + 1) * log2(10)) + 1) /
                                        static_cast<double>(COEFFICIENT_BIT_SIZE)) + 1;

        std::string eps = "0.";

        for (int i = 0; i < DECIMAL_PRECISION - 1; ++i) {
            eps.push_back('0');
        }
        eps.push_back('1');

        EPSILON = LargeFloatImplementation<T>(eps);
    }

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

        if (integralSource == "0" && fractionSource == "0") {
            return;
        }

        auto integral = LargeIntImplementation<T>(integralSource); // LSD -> MSD
        std::vector<T> fractionCoefficients = getFractionSourceCoefficients(fractionSource); // MSD -> LSD

        mantissa.coefficients.resize(fractionCoefficients.size() + integral.coefficients.size());
        std::copy(fractionCoefficients.rbegin(), fractionCoefficients.rend(), mantissa.coefficients.begin());
        std::copy(integral.coefficients.begin(), integral.coefficients.end(),
                  mantissa.coefficients.begin() + fractionCoefficients.size());

        trimFront(mantissa.coefficients, 0);

        exponent = integral.coefficients.size() - 1;
        exponent -= trimBack(mantissa.coefficients, 0);

        if (sign) {
            mantissa.negate();
        }
        mantissa.normalize();
    }

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(int n): mantissa(LargeIntImplementation<T>(n)) {
        exponent = std::max(0, static_cast<exponent_type>(mantissa.coefficients.size()) - 1);
    }

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(const LargeIntImplementation<T> &mantissa,
                                                          exponent_type exponent): mantissa(mantissa),
                                                                                   exponent(exponent) {}

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(double n) : exponent(0) {
        // TODO: optimize double conversion
        char str[FLOAT_MAX_DIGITS_COUNT + sizeof(char)];
        std::sprintf(str, "%.*f", std::numeric_limits<double>::digits10, n);
        *this = LargeFloatImplementation<T>(std::string(str));
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

        bool sign = getSign();
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

        std::string fractionalString;

        auto initialSize = fraction.coefficients.size();

        while (!areCoefficientsEmpty(fraction.coefficients) &&
               fractionalString.size() <= static_cast<size_t>(DECIMAL_PRECISION)) {
            fraction.multiplyByCoefficient(10);

            if (fraction.coefficients.size() > initialSize) {
                fractionalString += digitToChar(static_cast<uint8_t>(fraction.coefficients.back()));
                fraction.coefficients.pop_back();
            } else {
                fractionalString += '0';
            }
        }

        // Adjust last digit
        if (fractionalString.size() > static_cast<size_t>(DECIMAL_PRECISION)) {
            fraction.multiplyByCoefficient(10);
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

            if (integral.isZero() && sign) {
                result.erase(result.begin());
            }
        }

        return result;
    }

    template<class T>
    bool LargeFloatImplementation<T>::roundFractionalString(std::string &fraction) const {
        if (fraction.size() > static_cast<size_t>(DECIMAL_PRECISION)) {
            return roundStringNumber(fraction);
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
        if (exponent < 0 || mantissaCopy.coefficients.back() == 0) {
            fractionalCoefficients.resize(size);
            std::copy(begin, end,
                      fractionalCoefficients.begin());

            if (fractionalCoefficients.back() == 0) {
                fractionalCoefficients.pop_back();
            }

            integralCoefficients.push_back(0);

            if (exponent < 0) {
                fractionalCoefficients.insert(fractionalCoefficients.end(), -exponent - 1, 0);
            }
            return;
        }

        // Fractional part is 0
        if (static_cast<size_t>(exponent + 1) >= size) {
            integralCoefficients.resize(size);
            std::copy(begin, end, integralCoefficients.begin());
            integralCoefficients.insert(integralCoefficients.begin(), exponent + 1 - size, 0);
            return;
        }

        // There are both integral and fractional parts

        size_t integralSize = exponent + 1;
        size_t fractionSize = size - integralSize;

        integralCoefficients.resize(integralSize);
        fractionalCoefficients.resize(fractionSize);

        std::copy(begin, begin + fractionSize, fractionalCoefficients.begin());
        std::copy(begin + fractionSize, end, integralCoefficients.begin());
    }

    template<class T>
    size_t LargeFloatImplementation<T>::fractionSize() const {
        return mantissa.coefficients.size() - 1;
    }

    template<class T>
    void LargeFloatImplementation<T>::adjustPrecision() {
        size_t correctMantissaSize = PRECISION + std::max(exponent + 1, 0);

        if (mantissa.coefficients.size() > correctMantissaSize) {
            mantissa.coefficients.erase(mantissa.coefficients.begin(),
                                        mantissa.coefficients.end() - correctMantissaSize);
        }
    }

    template<class T>
    void LargeFloatImplementation<T>::multiply(const LargeFloatImplementation &multiplier) {
        std::size_t bothFractionSize = fractionSize() + multiplier.fractionSize();

        mantissa.multiply(multiplier.mantissa);

        exponent = exponent + multiplier.exponent + static_cast<exponent_type>(fractionSize() - bothFractionSize);

        if (mantissa.coefficients.empty()) {
            exponent = 0;
        }

        adjustPrecision();
    }

    template<class T>
    void LargeFloatImplementation<T>::add(LargeFloatImplementation<T> other) {
        exponent_type finalExponent = std::max(exponent, other.exponent);

        bool thisSign = getSign();
        bool otherSign = other.getSign();

        if (thisSign) {
            mantissa.negate();
        }

        if (otherSign) {
            other.mantissa.negate();
        }

        mantissa.coefficients.insert(mantissa.coefficients.end(), finalExponent - exponent, static_cast<T>(0));
        other.mantissa.coefficients.insert(other.mantissa.coefficients.end(), finalExponent - other.exponent,
                                           static_cast<T>(0));

        std::size_t maxSize = std::max(mantissa.coefficients.size(), other.mantissa.coefficients.size());

        mantissa.coefficients.insert(mantissa.coefficients.begin(), maxSize - mantissa.coefficients.size(),
                                     static_cast<T>(0));
        other.mantissa.coefficients.insert(other.mantissa.coefficients.begin(),
                                           maxSize - other.mantissa.coefficients.size(), static_cast<T>(0));

        if (thisSign) {
            mantissa.negate();
        }

        if (otherSign) {
            other.mantissa.negate();
        }

        mantissa.add(other.mantissa);

        finalExponent += mantissa.coefficients.size() - maxSize;

        maxSize = mantissa.coefficients.size();
        mantissa.normalize();
        finalExponent -= maxSize - mantissa.coefficients.size();
        trimFront(mantissa.coefficients, mantissa.getSupplementDigit());

        if (mantissa.coefficients.empty()) {
            mantissa.coefficients.push_back(mantissa.getSupplementDigit());
            exponent = 0;
        } else {
            exponent = finalExponent;
        }
    }

    template<class T>
    void LargeFloatImplementation<T>::subtract(LargeFloatImplementation<T> other) {
        other.negate();
        this->add(other);
    }

    template<class T>
    void LargeFloatImplementation<T>::negate() {
        mantissa.negate();
    }

    template<class T>
    bool LargeFloatImplementation<T>::getSign() const {
        return mantissa.sign;
    }

    template<class T>
    int LargeFloatImplementation<T>::compare(const LargeFloatImplementation<T> &other) {
        if (getSign() != other.getSign()) {
            if (getSign() > other.getSign()) {
                return -1;
            }

            return 1;
        }

        if (exponent != other.exponent) {
            bool isFirstZero = mantissa.isZero();
            bool isSecondZero = other.mantissa.isZero();

            if (isFirstZero) {
                return -1;
            } else if (isSecondZero) {
                return 1;
            }

            if (exponent > other.exponent) {
                return 1;
            }

            return -1;
        }

        LargeIntImplementation<T> firstMantissa = mantissa;
        LargeIntImplementation<T> secondMantissa = other.mantissa;

        bool wasNegated = false;

        if (firstMantissa.sign) {
            firstMantissa.negate();
            secondMantissa.negate();
            wasNegated = true;
        }

        std::size_t maxSize = std::max(firstMantissa.coefficients.size(), secondMantissa.coefficients.size());

        firstMantissa.coefficients.insert(firstMantissa.coefficients.begin(),
                                          maxSize - firstMantissa.coefficients.size(), 0);
        secondMantissa.coefficients.insert(secondMantissa.coefficients.begin(),
                                           maxSize - secondMantissa.coefficients.size(), 0);

        int mantissaComparisonResult = firstMantissa.compare(secondMantissa);
        if (wasNegated) {
            mantissaComparisonResult *= -1;
        }

        return mantissaComparisonResult;
    }

    template<class T>
    void LargeFloatImplementation<T>::divide(LargeFloatImplementation<T> divisor) {
        if (divisor.mantissa.isZero()) {
            throw std::invalid_argument("Cannot divide by zero!");
        }

        bool quotientSign = getSign() ^ divisor.getSign();

        if (getSign()) {
            mantissa.negate();
        }

        if (divisor.getSign()) {
            divisor.mantissa.negate();
        }

        exponent -= divisor.exponent + 1;
        divisor.exponent = -1;

        size_t maxIterations = 100;
        size_t iterations = 0;
        // Initial guess
        LargeFloatImplementation<T> x = getInitialGuess(divisor);
        LargeFloatImplementation<T> two(2);

        while (iterations < maxIterations) {
            LargeFloatImplementation<T> temp = divisor;
            temp.multiply(x);
            LargeFloatImplementation<T> multiplier = two;
            multiplier.subtract(temp);

            x.multiply(multiplier);

            if (multiplier.isCloseToOne()) {
                break;
            }

            ++iterations;
        }

        multiply(x);

        if (quotientSign) {
            mantissa.negate();
        }
    }

    template<class T>
    bool LargeFloatImplementation<T>::isCloseToOne() const {
        LargeFloatImplementation<T> copy = *this;
        copy.subtract(LargeFloatImplementation<T>(1));

        if (copy.getSign()) {
            copy.negate();
        }

        return copy.compare(EPSILON) <= 0;
    }

    template<class T>
    LargeFloatImplementation<T>
    LargeFloatImplementation<T>::getInitialGuess(const LargeFloatImplementation<T> &divisor) {
        // Taking initial division guess as described here https://en.wikipedia.org/wiki/Division_algorithm#Newton%E2%80%93Raphson_division
        LargeFloatImplementation<T> guess("2.8235294117647058823529411764706");

        LargeFloatImplementation<T> temp("1.8823529411764705882352941176471");
        temp.multiply(divisor);

        guess.subtract(temp);

        return guess;
    }

    template<class T>
    void LargeFloatImplementation<T>::floor() {
        if (exponent < 0) {
            exponent = 0;
            mantissa = LargeIntImplementation<T>(0);
            return;
        }

        if (exponent + 1 >= static_cast<exponent_type>(mantissa.coefficients.size())) {
            return;
        }

        size_t shift = mantissa.coefficients.size() - (exponent + 1);
        mantissa.coefficients.erase(mantissa.coefficients.begin(), mantissa.coefficients.begin() + shift);
    }

    template<class T>
    LargeFloatImplementation<T> &LargeFloatImplementation<T>::operator=(const LargeFloatImplementation<T> &other) {
        if (&other != this) {
            mantissa = other.mantissa;
            exponent = other.exponent;
        }

        return *this;
    }

    template<class T>
    bool LargeFloatImplementation<T>::isZero() const {
        return mantissa.isZero();
    }

    // For debugging
    template
    class LargeFloatImplementation<uint8_t>;

    // For final result
    template
    class LargeFloatImplementation<uint32_t>;
}
