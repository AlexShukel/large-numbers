//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOATIMPLEMENTATION_H
#define ND1_LARGEFLOATIMPLEMENTATION_H

#include <string>
#include <cmath>
#include <iostream>
#include "LargeIntImplementation.h"
#include "config.h"

namespace LargeNumbers {
    template<class T>
    class LargeFloatImplementation {
    private:
        friend class LargeFloatTester;

        LargeIntImplementation<T> mantissa;
        exponent_type exponent;

        static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
        static size_t PRECISION;
        static int DECIMAL_PRECISION;

        std::vector<T> getFractionSourceCoefficients(std::string source) const;

        void splitCoefficients(std::vector<T> &integralCoefficients, std::vector<T> &fractionalCoefficients,
                               const LargeIntImplementation<T> &mantissaCopy) const;

        bool roundFractionalString(std::string &fraction) const;

        size_t fractionSize() const;

        void adjustPrecision();

        bool isCloseToOne() const;

        LargeFloatImplementation getInitialGuess(const LargeFloatImplementation &divisor);

    public:
        static LargeFloatImplementation<T> EPSILON;

        LargeFloatImplementation();

        LargeFloatImplementation(const LargeFloatImplementation<T> &other);

        LargeFloatImplementation &operator=(const LargeFloatImplementation<T> &other);

        explicit LargeFloatImplementation(std::string number);

        explicit LargeFloatImplementation(int n);

        LargeFloatImplementation(const LargeIntImplementation<T> &mantissa, exponent_type exponent);

        explicit LargeFloatImplementation(double n);

        std::string toString() const;

        void multiply(const LargeFloatImplementation &multiplier);

        void add(LargeFloatImplementation other);

        void subtract(LargeFloatImplementation other);

        int compare(const LargeFloatImplementation &other);

        void negate();

        bool getSign() const;

        static void setDecimalPrecision(int precision);

        void divide(LargeFloatImplementation divisor);

        void floor();

        bool isZero() const;
    };
}

#endif //ND1_LARGEFLOATIMPLEMENTATION_H
