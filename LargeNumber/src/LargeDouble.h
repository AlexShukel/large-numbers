//
// Created by alexs on 2023-03-03.
//

#ifndef ND1_LARGEDOUBLE_H
#define ND1_LARGEDOUBLE_H

#include "LargeDoubleMath.h"
#include "LargeIntMath.h"
#include "config.h"
#include <string>
#include <cmath>

template<class T>
class LargeDouble {
private:
    LargeDoubleMath<T> math;
public:
    explicit LargeDouble();

    LargeDouble(LargeIntMath<T> mantissa, exponent_type exponent);

    explicit LargeDouble(const std::string &number);

    explicit LargeDouble(const LargeIntMath<T> &mantissa);

    std::string toString() const;

    LargeDouble operator*(const LargeDouble &other);

    LargeDouble &operator*=(const LargeDouble &other);

    LargeDouble operator+(const LargeDouble &other);

    LargeDouble &operator+=(const LargeDouble &other);

    LargeDouble operator/(const LargeDouble &other);

    LargeDouble &operator/=(const LargeDouble &other);
};


#endif //ND1_LARGEDOUBLE_H
