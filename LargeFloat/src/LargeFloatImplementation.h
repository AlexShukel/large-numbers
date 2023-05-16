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

    public:
        LargeFloatImplementation();

        LargeFloatImplementation(const LargeFloatImplementation<T> &other);

        explicit LargeFloatImplementation(const std::string &number);

        std::string toString() const;
    };
}

#endif //ND1_LARGEFLOATIMPLEMENTATION_H
