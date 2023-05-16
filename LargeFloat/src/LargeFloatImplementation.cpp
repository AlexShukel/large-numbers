//
// Created by alexs on 2023-05-16.
//

#include "LargeFloatImplementation.h"

namespace LargeNumbers {
    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(): mantissa(LargeIntImplementation<T>()), exponent(0) {}

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(const LargeFloatImplementation<T> &other): mantissa(
            other.mantissa), exponent(other.exponent) {}

    template<class T>
    LargeFloatImplementation<T>::LargeFloatImplementation(const std::string &number) {
        // TODO
    }

    template<class T>
    std::string LargeFloatImplementation<T>::toString() const {
        // TODO
        return "0";
    }

    // For debugging
    template
    class LargeFloatImplementation<uint8_t>;

    // For final result
    template
    class LargeFloatImplementation<uint32_t>;
}
