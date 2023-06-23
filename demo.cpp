//
// Created by alexs on 2023-06-21.
//

#include "LargeFloat.h"
#include "LargeInt.h"
#include "bubbleSort.h"
#include <cassert>
#include <iostream>

using namespace LargeNumbers;

int myFind(LargeFloat *numbers, const LargeFloat &number, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (numbers[i] == number) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void testFind() {
    LargeFloat numbers[] = {LargeFloat("512.0"), LargeFloat("0.0"), LargeFloat("1.5"), LargeFloat("-1.25")};
    const size_t n = sizeof(numbers) / sizeof(LargeFloat);
    assert(myFind(numbers, LargeFloat("1.5"), n) == 2);
    assert(myFind(numbers, LargeFloat("0.5"), n) == -1);
}

bool compare(const LargeFloat &a, const LargeFloat &b) {
    return a < b;
}

void checkArrayIsSorted(LargeFloat *arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        assert(arr[i - 1] <= arr[i]);
    }
}

void testSort() {
    LargeFloat numbers[] = {LargeFloat("512.0"), LargeFloat("0.0"), LargeFloat("1.5"), LargeFloat("-1.25")};
    const size_t n = sizeof(numbers) / sizeof(LargeFloat);
    bubbleSort(numbers, numbers + n, compare);
    checkArrayIsSorted(numbers, n);
}

LargeInt oneInt(1);
LargeInt twoInt(2);
LargeInt zeroInt(0);

LargeFloat twoFloat(2);

bool isPrime(const LargeInt &n) {
    if (n == oneInt) {
        return false;
    }

    for (LargeInt i = LargeInt(2); i * i <= n; i++) {
        if (n % i == zeroInt) {
            return false;
        }
    }

    return true;
}

LargeFloat findPrime(LargeFloat n) {
    n.ceil();

    std::string decimal = n.toString();
    decimal.erase(decimal.end() - 2, decimal.end());
    LargeInt integer(decimal);

    if (integer < twoInt) {
        return twoFloat;
    }

    while (!isPrime(integer)) {
        ++integer;
    }

    std::string finalDecimal = integer.toString();
    finalDecimal += ".0";

    return LargeFloat(finalDecimal);
}

void testPrime() {
    assert(findPrime(LargeFloat("0.0")).toString() == "2.0");
    assert(findPrime(LargeFloat("0.1")).toString() == "2.0");
    assert(findPrime(LargeFloat("1.9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999")).toString() == "2.0");
    assert(findPrime(LargeFloat("2.15")).toString() == "3.0");
    assert(findPrime(LargeFloat("6.33")).toString() == "7.0");
    assert(findPrime(LargeFloat("3275.0")).toString() == "3299.0");
    assert(findPrime(LargeFloat("6920.0")).toString() == "6947.0");
}

int main() {
    testFind();
    testSort();
    testPrime();

    std::cout << "Tests passed successfully!" << std::endl;
    return 0;
}
