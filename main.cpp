#include <iostream>
#include "LargeNumber.h"

int main() {
    LargeNumber a("456141.154564111");
    LargeNumber b("486456416.451321231121");

    LargeNumber sum = a + b;

    cout << sum.toString() << endl;
    return 0;
}
