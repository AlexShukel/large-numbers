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

    bool isPrime(const LargeInt &n) {
        LargeInt one(1);
        LargeInt zero(0);

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
        LargeInt two(2);

        if (n < two) {
            return two;
        }

        do {
            ++n;
        } while(!isPrime(n));

        return n;
    }

    LargeFloat pow(const LargeFloat &n, const LargeInt &p) {
        LargeInt one(1);
        LargeInt zero(0);

        if (p == zero) {
            return LargeFloat(1);
        }

        LargeFloat result = n;

        for (LargeInt i = one; i < p; ++i) {
            result *= n;
        }

        return result;
    }
}
