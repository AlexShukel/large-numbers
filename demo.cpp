//
// Created by alexs on 2023-06-21.
//

#include "LargeMath.h"
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

LargeFloat findPrime(LargeFloat n) {
    n.floor();

    std::string decimal = n.toString();
    decimal.erase(decimal.end() - 2, decimal.end());
    LargeInt integer(decimal);

    return LargeFloat(LargeNumbers::nextPrime(integer));
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

void testFactorial() {
    assert(factorial(LargeInt(0)).toString() == "1");
    assert(factorial(LargeInt(1)).toString() == "1");
    assert(factorial(LargeInt(2)).toString() == "2");
    assert(factorial(LargeInt(3)).toString() == "6");
    assert(factorial(LargeInt(4)).toString() == "24");
    assert(factorial(LargeInt(5)).toString() == "120");
    assert(factorial(LargeInt(100)).toString() == "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
}

int main() {
    testFactorial();
    testPrime();
    testFind();
    testSort();

    std::cout << "Tests passed successfully!" << std::endl;
    return 0;
}
