//
// Created by alexs on 2023-02-26.
// This class is used to leverage math logic for large integers
//

#ifndef ND1_LARGEINTMATH_H
#define ND1_LARGEINTMATH_H

#include <vector>
#include <cmath>
#include <string>

template<class T>
class LargeIntMath {
private:
    static constexpr size_t COEFFICIENT_SIZE = sizeof(T) * 8;
    size_t COEFFICIENT_BYTE_SIZE = pow(2, COEFFICIENT_SIZE);

    // 1 means '-' and 0 means '+'
    bool sign;
    // Coefficients are stored in reverse order: a0 * 256^0 + a1 * 256^1 + ... + ak * 256^k
    std::vector<T> coefficients;

public:
    explicit LargeIntMath();

    explicit LargeIntMath(const std::string &number);

    std::string toString() const;

    T getSupplementDigit() const;

    void add(const LargeIntMath<T> &addend);

#ifdef TEST_MODE
    std::vector<T> getCoefficients() const {
        return coefficients;
    }

    bool getSign() const {
        return sign;
    }

    void printCoefficients() const {
        for (auto x : coefficients) {
            std::cout << static_cast<int> (x) << " ";
        }
        std::cout << '\n';
    }
#endif
};


#endif //ND1_LARGEINTMATH_H
