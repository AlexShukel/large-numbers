#include <iostream>
#include <cmath>

int main() {
    double value = 123.456;
    int exponent;
    double mantissa = frexp(value, &exponent);

    std::cout << "Value: " << value << std::endl;
    std::cout << "Mantissa: " << mantissa << std::endl;
    std::cout << "Exponent: " << exponent << std::endl;

    return 0;
}
