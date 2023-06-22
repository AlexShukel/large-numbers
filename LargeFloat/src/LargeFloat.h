//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOAT_H
#define ND1_LARGEFLOAT_H

#include <string>

namespace LargeNumbers {
    class LargeFloat {
    private:
        class Implementation;

        Implementation *implementation;

    public:
        LargeFloat();

        // Copy constructor
        LargeFloat(const LargeFloat &other);

        // Copy assignment
        LargeFloat &operator=(const LargeFloat &other);

        // Move constructor
        LargeFloat(LargeFloat &&other) noexcept;

        // Move assignment
        LargeFloat &operator=(LargeFloat &&other) noexcept;

        explicit LargeFloat(const std::string &number);

        explicit LargeFloat(int n);

        ~LargeFloat();

        std::string toString() const;

        LargeFloat operator*(const LargeFloat &multiplier);

        LargeFloat &operator*=(const LargeFloat &multiplier);

        LargeFloat operator/(const LargeFloat &other);

        LargeFloat &operator/=(const LargeFloat &other);

        LargeFloat operator+(const LargeFloat &other);

        LargeFloat &operator+=(const LargeFloat &other);

        LargeFloat &operator++();

        const LargeFloat operator++(int);

        LargeFloat operator+() const;

        LargeFloat operator-(const LargeFloat &other);

        LargeFloat &operator-=(const LargeFloat &other);

        LargeFloat &operator--();

        const LargeFloat operator--(int);

        LargeFloat operator-() const;

        bool operator<(const LargeFloat &other) const;

        bool operator<=(const LargeFloat &other) const;

        bool operator>(const LargeFloat &other) const;

        bool operator>=(const LargeFloat &other) const;

        bool operator==(const LargeFloat &other) const;

        bool operator!=(const LargeFloat &other) const;
    };
}

#endif //ND1_LARGEFLOAT_H
