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

void decimalStringToNumbers(std::vector<uint8_t> &output, const std::string &source);

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
size_t trimFront(std::vector<T> &container, T value) {
    auto it = std::find_if_not(container.begin(), container.end(), Equal<T>(value));
    size_t count = std::distance(container.begin(), it);
    container.erase(container.begin(), it);
    return count;
}

template<class T>
size_t trimBack(std::vector<T> &container, T value) {
    auto it = std::find_if_not(container.rbegin(), container.rend(), Equal<T>(value));
    size_t count = std::distance(container.rbegin(), it);
    container.erase(it.base(), container.end());
    return count;
}

#endif //ND1_UTILS_H
