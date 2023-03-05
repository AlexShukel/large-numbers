//
// Created by alexs on 2023-03-04.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <cinttypes>
#include <string>
#include <algorithm>
#include <vector>

inline uint8_t charToDigit(char character) {
    return character - 48;
}

inline char digitToChar(uint8_t digit) {
    return digit + 48;
}

inline bool isZero(const std::string &number) {
    return std::all_of(number.begin(), number.end(), [](char c) { return c == '0'; });
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

template<class T>
bool areCoefficientsEmpty(const std::vector<T> &coefficients) {
    return std::all_of(coefficients.begin(), coefficients.end(), [](T value) {
        return value == 0;
    });
}

template<class T>
size_t trimFront(std::vector<T> &container, T value) {
    auto it = std::find_if_not(container.begin(), container.end(), Equal<T>(value));
    size_t count = std::distance(container.begin(), it);
    container.erase(container.begin(), it);
    return count;
}

template<class T, class V>
size_t trimBack(T &container, V value) {
    auto it = std::find_if_not(container.rbegin(), container.rend(), Equal<V>(value));
    size_t count = std::distance(container.rbegin(), it);
    container.erase(it.base(), container.end());
    return count;
}

template<class T>
void extendFront(std::vector<T> &container, T value, uint64_t count) {
    if (count == 0) {
        return;
    }

    container.insert(container.begin(), count, value);
}

template<class T>
void extendBack(std::vector<T> &container, T value, uint64_t count) {
    if (count == 0) {
        return;
    }

    container.insert(container.end(), count, value);
}

size_t getAbsoluteDelta(int64_t a, int64_t b);

#endif //ND1_UTILS_H
