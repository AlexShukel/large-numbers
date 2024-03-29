//
// Created by alexs on 2023-05-16.
//

#ifndef ND1_LARGEFLOAT_H
#define ND1_LARGEFLOAT_H

#include "LargeInt.h"
#include <string>

namespace LargeNumbers {
    class LargeFloat {
    private:
        friend class LargeInt;

        class Implementation;

        Implementation *implementation;

    public:
        static const LargeFloat epsilon;
        static const LargeFloat pi;

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

        explicit LargeFloat(const LargeInt &n);

        explicit LargeFloat(Implementation *impl);

        // Primitive data type constructors
        explicit LargeFloat(int n);

        explicit LargeFloat(double n);

        ~LargeFloat();

        std::string toString() const;

        LargeFloat operator*(const LargeFloat &multiplier) const;

        LargeFloat &operator*=(const LargeFloat &multiplier);

        LargeFloat operator/(const LargeFloat &other) const;

        LargeFloat &operator/=(const LargeFloat &other);

        LargeFloat operator+(const LargeFloat &other) const;

        LargeFloat &operator+=(const LargeFloat &other);

        LargeFloat &operator++();

        const LargeFloat operator++(int);

        LargeFloat operator+() const;

        LargeFloat operator-(const LargeFloat &other) const;

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

        void ceil();

        void floor();

        bool isZero() const;

        LargeFloat abs() const;
    };
}

#endif //ND1_LARGEFLOAT_H
