//
// Created by alexs on 2023-02-19.
//

#ifndef ND1_LARGEINT_H
#define ND1_LARGEINT_H

#include <string>
#include <vector>
#include <cmath>
#include <iterator>
#include "LargeIntMath.h"

class LargeNumberInitException : public std::exception {
private:
    const std::string &message;

public:
    explicit LargeNumberInitException(const std::string &msg);

    const char *what();
};

// Class to store large whole numbers.
template<class T>
class LargeInt {
private:
    LargeIntMath<T> *math;

public:
    explicit LargeInt(const std::string &number);

    ~LargeInt();

    std::string toString() const;

    LargeInt operator+(const LargeInt<T> &other);

    LargeInt operator+=(const LargeInt<T> &other);
};

#endif //ND1_LARGEINT_H
