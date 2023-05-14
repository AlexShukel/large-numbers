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

        std::string toString() const;
    };
}

#endif //ND1_LARGEINT_H
