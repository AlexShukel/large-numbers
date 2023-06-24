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
        } while (!isPrime(n));

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

    LargeFloat ln(const LargeFloat &x) {
        LargeFloat one(1);
        LargeFloat zero(0);

        if (x == one) {
            return zero;
        }

        LargeFloat result;

        LargeFloat currentTerm = x - one;

        int terms = 331; // Number of Taylor series expansion terms
        LargeFloat n(terms + 2);
        LargeFloat temp = one - x;

        for (LargeFloat i = LargeFloat(2); i < n; ++i) {
            result += currentTerm;

            currentTerm *= (i - one) * temp / i; // Recursive formula for n-th term of Taylor series expansion
        }

        return result;
    }

    LargeFloat sqrt(const LargeFloat &value) {
        LargeFloat x = value;
        LargeFloat y(1);
        LargeFloat two(2);

        while ((x - y).abs() > LargeFloat::epsilon) {
            x += y;
            x /= two;
            y = value / x;
        }

        return x;
    }
}
