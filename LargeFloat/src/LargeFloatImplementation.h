//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOATIMPLEMENTATION_H
#define ND1_LARGEFLOATIMPLEMENTATION_H

#include <string>
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
        static constexpr size_t DECIMAL_PRECISION = 100;
        static constexpr size_t PRECISION = 332.1928094887362347870 / COEFFICIENT_BIT_SIZE + 1;

        std::vector<T> getFractionSourceCoefficients(std::string source) const;

        void splitCoefficients(std::vector<T> &integralCoefficients, std::vector<T> &fractionalCoefficients,
                               const LargeIntImplementation<T> &mantissaCopy) const;

    public:
        LargeFloatImplementation();

        LargeFloatImplementation(const LargeFloatImplementation<T> &other);

        explicit LargeFloatImplementation(std::string number);

        std::string toString() const;
    };
}

#endif //ND1_LARGEFLOATIMPLEMENTATION_H
