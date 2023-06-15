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

        explicit LargeFloat(const std::string &number);

        ~LargeFloat();

        std::string toString() const;

        LargeFloat operator*(const LargeFloat &multiplier);

        LargeFloat &operator*=(const LargeFloat &multiplier);
    };
}

#endif //ND1_LARGEFLOAT_H
