#include <iostream>
#include <vector>
#include <cassert>
#include <bitset>
#include <algorithm>
#include <cmath>
#include "LargeIntImplementation.h"

/**
 * Generic type T defines the base of numbers stored in vector
 * @example
 * When T is uint8_t (8 bits), then numbers are stored like a0 * 2^8^0 + a1 * 2^8^1 + ... + an * 2^8^n
 * When T is uint32_t (32 bits), then numbers are stored like a0 * 2^32^0 + a1 * 2^32^1 + ... + an * 2^32^n
 */

//class LargeNumbers::LargeIntTester {
//public:
//    static void run() {
//        LargeNumbers::LargeIntImplementation<uint8_t> integer("100");
//        for (auto it = integer.coefficients.begin(); it != integer.coefficients.end(); ++it) {
//            std::cout << static_cast<int>(*it) << " ";
//        }
//    }
//};

template<class T>
class Equal {
    T value;
public:
    explicit Equal(T value) : value(value) {
    }

    bool operator()(T another) {
        return value == another;
    }
};

int main() {
    std::cout << floorf(-1.5f);

    return 0;
}
