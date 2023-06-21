//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <cstdint>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>

uint8_t charToDigit(char character);

char digitToChar(uint8_t digit);

bool isStringZero(const std::string &number);

uint8_t euclideanDivision(std::string &binary);

template<class T>
bool areCoefficientsEmpty(const std::vector<T> &coefficients) {
    return std::all_of(coefficients.begin(), coefficients.end(), [](const T &c) {
        return c == 0;
    });
}

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

template<class T, class V>
size_t trimFrontNotLast(T &container, V value) {
    auto it = std::find_if_not(container.begin(), container.end(), Equal<V>(value));

    // Retain one element in container
    if (it != container.begin()) {
        --it;
    }

    size_t count = std::distance(container.begin(), it);
    container.erase(container.begin(), it);
    return count;
}

template<class T, class V>
size_t trimBackNotLast(T &container, V value) {
    auto it = std::find_if_not(container.rbegin(), container.rend(), Equal<V>(value));

    // Retain one element in container
    if (it.base() != container.end()) {
        --it;
    }

    size_t count = std::distance(container.rbegin(), it);
    container.erase(it.base(), container.end());
    return count;
}

#endif //ND1_UTILS_H
