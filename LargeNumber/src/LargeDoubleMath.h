//
// Created by alexs on 2023-03-03.
//

#ifndef ND1_LARGEDOUBLEMATH_H
#define ND1_LARGEDOUBLEMATH_H

#include "LargeIntMath.h"
#include "config.h"

template<class T>
class LargeDoubleMath {
private:
    bool sign;
    LargeIntMath<T> mantissa;
    exponent_type exponent;

    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
public:
    explicit LargeDoubleMath();

    LargeDoubleMath(LargeIntMath<T> mantissa, exponent_type exponent, bool sign);

    LargeDoubleMath(const std::string &number);
};


#endif //ND1_LARGEDOUBLEMATH_H
