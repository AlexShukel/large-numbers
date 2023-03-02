//
// Created by alexs on 2023-02-19.
// This class provides public API for operations with large integers
//

#ifndef ND1_LARGEINT_H
#define ND1_LARGEINT_H

#include "LargeIntMath.h"

// Class to store large whole numbers.
template<class T>
class LargeInt {
private:
    LargeIntMath<T> math;

public:
    explicit LargeInt(const std::string &number);

    std::string toString() const;

    LargeInt operator+(const LargeInt<T> &other);

    LargeInt &operator+=(const LargeInt<T> &other);
};

#endif //ND1_LARGEINT_H
