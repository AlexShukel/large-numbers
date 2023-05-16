//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_LARGEINT_H
#define ND1_LARGEINT_H

#include <string>

namespace LargeNumbers {
    class LargeInt {
    private:
        class Implementation;

        Implementation *implementation;

    public:
        LargeInt();

        LargeInt(const LargeInt &other);

        explicit LargeInt(const std::string &number);

        ~LargeInt();

        LargeInt &operator=(const LargeInt &other);

        LargeInt operator+(const LargeInt &other);

        LargeInt &operator+=(const LargeInt &other);

        LargeInt &operator++();

        const LargeInt operator++(int);

        LargeInt operator-(const LargeInt &other) const;

        LargeInt &operator-=(const LargeInt &other);

        LargeInt &operator--();

        const LargeInt operator--(int);

        LargeInt operator*(const LargeInt &other);

        LargeInt &operator*=(const LargeInt &other);

        LargeInt operator/(const LargeInt &other);

        LargeInt &operator/=(const LargeInt &other);

        bool operator==(const LargeInt &other) const;

        bool operator!=(const LargeInt &other) const;

        bool operator<(const LargeInt &other) const;

        bool operator>(const LargeInt &other) const;

        bool operator<=(const LargeInt &other) const;

        bool operator>=(const LargeInt &other) const;

        std::string toString() const;
    };
}

#endif //ND1_LARGEINT_H
