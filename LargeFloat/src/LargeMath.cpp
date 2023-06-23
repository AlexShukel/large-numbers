//
// Created by Aleksandras on 2023-06-23.
//

#include "LargeMath.h"

namespace LargeNumbers {
    LargeInt factorial(const LargeInt &n) {
        LargeInt result(1);

        for (LargeInt i = LargeInt(2); i <= n; ++i) {
            result *= i;
        }

        return result;
    }
}
