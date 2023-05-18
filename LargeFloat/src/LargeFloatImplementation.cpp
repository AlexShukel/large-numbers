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

        if (sign) {
            number.erase(number.begin());
        }

        size_t pointIndex = number.find('.');

        std::string integralSource = number.substr(0, pointIndex);
        std::string fractionSource = number.substr(pointIndex + 1);

        auto integral = LargeIntImplementation<T>(integralSource);
        std::vector<T> fractionCoefficients = getFractionSourceCoefficients(fractionSource);

        if (integral.isZero()) {
            size_t trimmedZeros = 0;
            auto it = std::find_if_not(fractionCoefficients.begin(), fractionCoefficients.end(), [](const T &c) {
                return c == 0;
            });
            fractionCoefficients.erase(fractionCoefficients.begin(), it);
            exponent = -static_cast<exponent_type>(trimmedZeros);
        } else {
            exponent = static_cast<exponent_type>(integral.coefficients.size() - 1);
        }

        mantissa.coefficients.resize(integral.coefficients.size() + fractionCoefficients.size());
        std::copy(integral.coefficients.rbegin(), integral.coefficients.rend(), mantissa.coefficients.begin());
        std::copy(fractionCoefficients.begin(), fractionCoefficients.end(),
                  mantissa.coefficients.begin() + integral.coefficients.size());

        mantissa.normalize();
        if (sign) {
            mantissa.sign = true;
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
