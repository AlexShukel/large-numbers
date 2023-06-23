//
// Created by Aleksandras on 2023-06-23.
//

#include "LargeMath.h"

namespace LargeNumbers {
    LargeInt one(1);
    LargeInt two(2);
    LargeInt zero(0);

    LargeInt factorial(const LargeInt &n) {
        LargeInt result(1);

        for (LargeInt i = LargeInt(2); i <= n; ++i) {
            result *= i;
        }

        return result;
    }

    bool isPrime(const LargeInt &n) {
        if (n == one) {
            return false;
        }

        for (LargeInt i = LargeInt(2); i * i <= n; i++) {
            if (n % i == zero) {
                return false;
            }
        }

        return true;
    }

    LargeInt nextPrime(LargeInt n) {
        if (n < two) {
            return two;
        }

        do {
            ++n;
        } while(!isPrime(n));

        return n;
    }
}
