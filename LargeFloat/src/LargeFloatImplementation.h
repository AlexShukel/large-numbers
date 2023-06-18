//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOATIMPLEMENTATION_H
#define ND1_LARGEFLOATIMPLEMENTATION_H

#include <string>
#include <cmath>
#include "LargeIntImplementation.h"
#include "../../config.h"

namespace LargeNumbers {
    template<class T>
    class LargeFloatImplementation {
    private:
        friend class LargeFloatTester;

        LargeIntImplementation<T> mantissa;
        exponent_type exponent;

        static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
        static constexpr size_t PRECISION = static_cast<size_t>(336.0 / static_cast<double>(COEFFICIENT_BIT_SIZE)) + 1;
        static int DECIMAL_PRECISION;

        std::vector<T> getFractionSourceCoefficients(std::string source) const;

        void splitCoefficients(std::vector<T> &integralCoefficients, std::vector<T> &fractionalCoefficients,
                               const LargeIntImplementation<T> &mantissaCopy) const;

        bool roundFractionalString(std::string &fraction) const;

        void normalize();

        void shiftRight(size_t n);

    public:
        LargeFloatImplementation();

        LargeFloatImplementation(const LargeFloatImplementation<T> &other);

        explicit LargeFloatImplementation(std::string number);

        std::string toString() const;

        static void setDecimalPrecision(int precision);

        void multiply(const LargeFloatImplementation &multiplier);

        void add(LargeFloatImplementation other);
    };
}

#endif //ND1_LARGEFLOATIMPLEMENTATION_H
