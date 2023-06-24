//
// Created by Aleksandras on 2023-06-23.
//

#include "LargeMath.h"
#include "TemplateMath.h"
#include "utils.h"

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

    LargeFloat pow(const LargeFloat &n, int p) {
        return TemplateMath::pow(n, p);
    }

    LargeInt pow(const LargeInt &n, int p) {
        return TemplateMath::pow(n, p);
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

    LargeFloat pi(int precision) {
        LargeFloat sum(0);
        LargeInt a(1103);
        LargeInt b(26390);
        LargeInt c(396);
        int iterationCount = precision / 8 + 1;

        for (int i = 0; i < iterationCount; ++i) {
            LargeInt value = factorial(LargeInt(4 * i)) * (a + b * LargeInt(i));
            LargeInt temp = factorial(LargeInt(i));
            LargeInt secondValue = temp * temp * temp * temp * pow(c, 4 * i);

            LargeFloat term = LargeFloat(value) / LargeFloat(secondValue);
            sum += term;
        }

        LargeFloat temp = LargeFloat(2) * sqrt(LargeFloat(2)) / LargeFloat(9801);
        LargeFloat invertedPi = sum * temp;

        LargeFloat pi = LargeFloat(1) / invertedPi;

        std::string fraction = pi.toString().substr(2);
        if (precision + 1 < fraction.size()) {
            fraction.erase(fraction.begin() + precision + 1, fraction.end());
            roundStringNumber(fraction);
        }
        return LargeFloat("3." + fraction);
    }
}
