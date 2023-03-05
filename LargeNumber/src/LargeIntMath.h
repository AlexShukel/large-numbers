//
// Created by alexs on 2023-02-26.
// This class is used to leverage math logic for large integers
//

#ifndef ND1_LARGEINTMATH_H
#define ND1_LARGEINTMATH_H

#include <vector>
#include <cmath>
#include <string>
#include <limits>

template<class T>
class LargeIntMath {
private:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
    static constexpr T maxValue = std::numeric_limits<T>::max();

    // 1 means '-' and 0 means '+'
    bool sign;
    // Coefficients are stored in reverse order: a0 * 256^0 + a1 * 256^1 + ... + ak * 256^k
    std::vector<T> coefficients;
public:
    explicit LargeIntMath();

    explicit LargeIntMath(const std::string &number);

    LargeIntMath(std::vector<T> coefficients, bool sign);

    std::vector<T> &getCoefficients();

    std::vector<T> getCoefficients() const;

    bool &getSign();

    bool getSign() const;

    std::string toString() const;

    T getSupplementDigit() const;

    void negate();

    void positivate();

    void shiftLeft(int shift);

    T getMaxValue() const;

    // Multiply positive number by given coefficient.
    void multiplyByCoefficient(T coefficient);

    void add(const LargeIntMath &addend);

    void subtract(LargeIntMath subtrahend);

    void multiply(LargeIntMath multiplier);

    int compare(const LargeIntMath &other) const;
};


#endif //ND1_LARGEINTMATH_H
