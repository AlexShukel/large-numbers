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
    LargeIntMath<T> mantissa;
    exponent_type exponent;

    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
public:
    explicit LargeDoubleMath();

    LargeDoubleMath(LargeIntMath<T> mantissa, exponent_type exponent);

    explicit LargeDoubleMath(const std::string &number);

    explicit LargeDoubleMath(LargeIntMath<T> mantissa);

    bool getSign() const;

    bool &getSign();

    LargeIntMath<T> getMantissa() const;

    LargeIntMath<T> &getMantissa();

    exponent_type getExponent() const;

    exponent_type &getExponent();

    void normalize();

    void multiply(const LargeDoubleMath<T> &multiplier);
};


#endif //ND1_LARGEDOUBLEMATH_H
