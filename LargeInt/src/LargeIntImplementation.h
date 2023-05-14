//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_LARGEINTIMPLEMENTATION_H
#define ND1_LARGEINTIMPLEMENTATION_H

#include <vector>
#include <string>

namespace LargeNumbers {
    template<class T>
    class LargeIntImplementation {
    private:
        friend class LargeIntTester;

        static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;

        bool sign;
        std::vector<T> coefficients;

        void coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients) const;

    public:
        LargeIntImplementation();

        LargeIntImplementation(const LargeIntImplementation<T> &other);

        explicit LargeIntImplementation(const std::string &number);

        LargeIntImplementation(const std::vector<T> &coefficients, bool sign);

        std::string toString() const;
    };
}

#endif //ND1_LARGEINTIMPLEMENTATION_H
