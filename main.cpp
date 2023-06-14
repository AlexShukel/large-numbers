#include <iostream>
#include <vector>
#include <cassert>
#include <bitset>
#include <algorithm>
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
//    std::vector<int> v = {1, 1, 1};
//    auto it = std::find_if_not(v.rbegin(), v.rend(), Equal<int>(1));
//
//    if (it.base() == v.begin()) {
//        --it;
//        std::cout << std::distance(v.begin(), it.base());
//    }
    int a = -5, b = 1;
    std::cout << a % b;
    return 0;
}
