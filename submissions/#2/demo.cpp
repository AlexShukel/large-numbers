//
// Created by alexs on 2023-06-21.
//

#include "LargeFloat.h"
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

int main() {
    testFind();
    testSort();

    std::cout << "Tests passed successfully!" << std::endl;
    return 0;
}
