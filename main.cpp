#include <iostream>
#include <vector>
#include <cassert>

/**
 * Generic type T defines the base of numbers stored in vector
 * @example
 * When T is uint8_t (8 bits), then numbers are stored like a0 * 2^8^0 + a1 * 2^8^1 + ... + an * 2^8^n
 * When T is uint32_t (32 bits), then numbers are stored like a0 * 2^32^0 + a1 * 2^32^1 + ... + an * 2^32^n
 */

int main() {
    std::cout << 5 % -3 << std::endl;
    return 0;
}
