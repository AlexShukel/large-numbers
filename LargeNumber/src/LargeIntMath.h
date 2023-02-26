//
// Created by alexs on 2023-02-26.
// This class is used to leverage math logic
//

#ifndef ND1_LARGEINTMATH_H
#define ND1_LARGEINTMATH_H

#include <vector>
#include "LargeInt.h"

template<class T>
class LargeIntMath {
private:
    static constexpr size_t COEFFICIENT_SIZE = sizeof(T) * 8;

    // 1 means '-' and 0 means '+'
    bool sign;
    // Coefficients are stored in reverse order: a0 * 256^0 + a1 * 256^1 + ... + ak * 256^k
    std::vector<T> coefficients;

public:
    explicit LargeIntMath();

    LargeIntMath(std::vector<T> coefficients, bool sign);

    void add(const LargeIntMath<T> &addend);

#ifdef TEST_MODE
    int getValue() const {
        int v = 0, i = 0;

        for (auto x: coefficients) {
            v += x * pow(256, i);
            ++i;
        }

        return v;
    }
#endif
};


#endif //ND1_LARGEINTMATH_H
