//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOATIMPLEMENTATION_H
#define ND1_LARGEFLOATIMPLEMENTATION_H

#include <string>
#include <cmath>
#include <iostream>
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
        static size_t PRECISION;
        static int DECIMAL_PRECISION;

        std::vector<T> getFractionSourceCoefficients(std::string source) const;

        void splitCoefficients(std::vector<T> &integralCoefficients, std::vector<T> &fractionalCoefficients,
                               const LargeIntImplementation<T> &mantissaCopy) const;

        bool roundFractionalString(std::string &fraction) const;

        size_t fractionSize() const;

        void adjustPrecision();

    public:
        LargeFloatImplementation();

        LargeFloatImplementation(const LargeFloatImplementation<T> &other);

        explicit LargeFloatImplementation(std::string number);

        explicit LargeFloatImplementation(int n);

        std::string toString() const;

        void multiply(const LargeFloatImplementation &multiplier);

        void add(LargeFloatImplementation other);

        int compare(const LargeFloatImplementation &other);
    };
}

#endif //ND1_LARGEFLOATIMPLEMENTATION_H
