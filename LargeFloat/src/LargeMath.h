//
// Created by Aleksandras on 2023-06-23.
//

#ifndef ND1_LARGEMATH_H
#define ND1_LARGEMATH_H

#include "LargeFloat.h"
#include "LargeInt.h"

namespace LargeNumbers {
    // Finds factorial of a given number
    LargeInt factorial(const LargeInt &n);

    // Finds the next prime number greater than n
    LargeInt nextPrime(LargeInt n);

    // Raise n to the power p
    LargeFloat pow(const LargeFloat &n, const LargeInt &p);

    // Finds the natural log of x
    LargeFloat ln(const LargeFloat &x);

    // Finds the square root of x
    LargeFloat sqrt(const LargeFloat &value);
}

#endif //ND1_LARGEMATH_H
