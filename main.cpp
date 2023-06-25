#include <iostream>
#include <limits>

int main() {
    uint32_t n = std::numeric_limits<uint32_t>::max();
    std::cout << n << std::endl;
    uint64_t x = static_cast<uint64_t>(n) * static_cast<uint64_t>(n);
    std::cout << x;
    return 0;
}
