#include <iostream>
#include <vector>
#include <string>
#include "LargeNumber.h"

typedef uint8_t byte;

int main() {
    std::vector<byte> c1 = {13, 111};
    std::vector<byte> c2 = {17, 3, 1};

    LargeNumber<byte> num1(c1, false);
    LargeNumber<byte> num2(c2, false);

    LargeNumber<byte> sum = num1 + num2;
    std::cout << sum.getValue();

    return 0;
}
