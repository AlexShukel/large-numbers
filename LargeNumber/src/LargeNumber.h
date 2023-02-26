//
// Created by alexs on 2023-02-19.
//

#ifndef ND1_LARGENUMBER_H
#define ND1_LARGENUMBER_H

#include <string>
#include <vector>
#include <cmath>
#include <iterator>

#define DEBUG 1

template<class T>
class LargeNumber {
private:
    // Coefficients are stored in reverse order: a0 * 256^0 + a1 * 256^1 + ... + ak * 256^k
    std::vector<T> coefficients;
    bool sign;

    static void additionImpl(LargeNumber<T> &first, const LargeNumber<T> &second);

public:
    LargeNumber(std::vector<T> coefficients, bool sign);

    LargeNumber operator+(const LargeNumber<T> &other);

#ifdef DEBUG

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

#endif //ND1_LARGENUMBER_H
