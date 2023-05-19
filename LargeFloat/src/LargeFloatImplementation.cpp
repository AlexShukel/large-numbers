//
// Created by alexs on 2023-05-16.
//

#include "LargeFloatImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>

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
        // TODO
        return "0";
    }

    // For debugging
    template
    class LargeFloatImplementation<uint8_t>;

    // For final result
    template
    class LargeFloatImplementation<uint32_t>;
}
