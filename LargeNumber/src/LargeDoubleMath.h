//
// Created by alexs on 2023-03-03.
//

#ifndef ND1_LARGEDOUBLEMATH_H
#define ND1_LARGEDOUBLEMATH_H

#include "LargeIntMath.h"
#include "config.h"
#include <bitset>

template<class T>
class LargeDoubleMath {
private:
    LargeIntMath<T> mantissa;
    exponent_type exponent;

    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
    static constexpr size_t PRECISION = 332.1928094887362347870 / COEFFICIENT_BIT_SIZE;
public:
    explicit LargeDoubleMath();

    LargeDoubleMath(LargeIntMath<T> mantissa, exponent_type exponent);

    explicit LargeDoubleMath(const std::string &number);

    explicit LargeDoubleMath(LargeIntMath<T> mantissa);

    std::string toString() const;

    bool getSign() const;

    bool &getSign();

    LargeIntMath<T> getMantissa() const;

    LargeIntMath<T> &getMantissa();

    void setMantissa(LargeIntMath<T> mantissa);

    exponent_type getExponent() const;

    exponent_type &getExponent();

    void setExponent(exponent_type exponent);

    void normalize();

    size_t getFractionalPartSize() const;

    std::vector<T> getIntegralCoefficients() const;

    std::vector<T> getFractionalCoefficients() const;

    static constexpr size_t getCurrentBase();

    void multiply(const LargeDoubleMath<T> &multiplier);

    void add(LargeDoubleMath<T> addend);

    void divide(const LargeDoubleMath<T> &divider);
};


#endif //ND1_LARGEDOUBLEMATH_H
