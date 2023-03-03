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

    LargeInt &operator=(const LargeInt &other);

    LargeInt operator+(const LargeInt &other);

    LargeInt operator+();

    LargeInt &operator+=(const LargeInt &other);

    LargeInt &operator++();

    const LargeInt operator++(int);

    LargeInt operator-(const LargeInt &other) const;

    LargeInt operator-() const;

    LargeInt &operator-=(const LargeInt &other);

    LargeInt &operator--();

    const LargeInt operator--(int);

    LargeInt operator*(const LargeInt &other);

    LargeInt &operator*=(const LargeInt &other);

    bool operator==(const LargeInt &other) const;

    bool operator!=(const LargeInt &other) const;

    bool operator<(const LargeInt &other) const;

    bool operator>(const LargeInt &other) const;

    bool operator<=(const LargeInt &other) const;

    bool operator>=(const LargeInt &other) const;
};

#endif //ND1_LARGEINT_H
