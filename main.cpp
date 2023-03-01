#include <iostream>
#include "LargeInt.h"

using namespace std;

int main() {
    LargeInt<uint8_t> a("1");
    LargeInt<uint8_t> b("1");
    LargeInt<uint8_t> sum = a + b;

//    cout << sum.toString();
    return 0;
}
