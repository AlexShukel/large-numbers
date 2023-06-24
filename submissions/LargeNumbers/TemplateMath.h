//
// Created by alexs on 2023-06-24.
//

#ifndef ND1_TEMPLATEMATH_H
#define ND1_TEMPLATEMATH_H

#include <stdexcept>

namespace TemplateMath {
    template<class ArgType>
    ArgType pow(const ArgType &n, int p) {
        if (p < 0) {
            throw std::logic_error("The power must be positive integer!");
        }

        if (p == 0) {
            return ArgType(1);
        }

        ArgType result = n;

        for (int i = 1; i < p; ++i) {
            result *= n;
        }

        return result;
    }
}

#endif //ND1_TEMPLATEMATH_H
