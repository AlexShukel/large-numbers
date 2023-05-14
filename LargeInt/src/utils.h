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

bool isZero(const std::string &number);

uint8_t euclideanDivision(std::string &binary);

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

template<class T, class V>
size_t trimBack(T &container, V value) {
    auto it = std::find_if_not(container.rbegin(), container.rend(), Equal<V>(value));
    size_t count = std::distance(container.rbegin(), it);
    container.erase(it.base(), container.end());
    return count;
}

template<class T>
void toTwosComplement(std::vector<T> &coefficients) {
    T carry = 1;

    for (auto &c: coefficients) {
        c = ~c;

        T prevC = c;
        c += carry;

        if (c > prevC) {
            carry = 0;
        }
    }
}

#endif //ND1_UTILS_H
