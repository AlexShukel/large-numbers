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

        LargeFloat(const LargeFloat &other);

        LargeFloat &operator=(const LargeFloat &other);

        explicit LargeFloat(const std::string &number);

        LargeFloat(LargeFloat &&other) noexcept;

        LargeFloat &operator=(LargeFloat &&other) noexcept;

        ~LargeFloat();

        std::string toString() const;

        LargeFloat operator*(const LargeFloat &multiplier);

        LargeFloat &operator*=(const LargeFloat &multiplier);

        LargeFloat operator+(const LargeFloat &other);

        LargeFloat &operator+=(const LargeFloat &other);

        bool operator<(const LargeFloat &other) const;

        bool operator<=(const LargeFloat &other) const;

        bool operator>(const LargeFloat &other) const;

        bool operator>=(const LargeFloat &other) const;

        bool operator==(const LargeFloat &other) const;

        bool operator!=(const LargeFloat &other) const;
    };
}

#endif //ND1_LARGEFLOAT_H
