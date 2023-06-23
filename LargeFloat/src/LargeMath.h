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
}

#endif //ND1_LARGEMATH_H
