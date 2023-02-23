//
// Created by alexs on 2023-02-19.
//

#include <algorithm>
#include "LargeNumber.h"

static inline bool isFractionalPartSeparator(char c) {
    return c == '.' || c == ',';
}

void LargeNumber::getFractionalPart(std::string &fraction) const {
    bool isIntegerPart = true;

    for (auto c: number) {
        if (isFractionalPartSeparator(c)) {
            isIntegerPart = false;
        } else if (!isIntegerPart) {
            fraction.push_back(c);
        }
    }
}

void LargeNumber::getIntegerPart(std::string &integer) const {
    bool isIntegerPart = true;

    for (auto c: number) {
        if (isFractionalPartSeparator(c)) {
            isIntegerPart = false;
        } else if (isIntegerPart) {
            integer.push_back(c);
        }
    }
}

void LargeNumber::sumFractionalParts(const LargeNumber &another, std::string &fraction) {
    std::string numberPart, anotherNumberPart;
    getFractionalPart(numberPart);
    another.getFractionalPart(anotherNumberPart);

    // anotherNumber must be greater than number by length
    if (numberPart.length() > anotherNumberPart.length()) {
        std::string tmp = numberPart;
        numberPart = anotherNumberPart;
        anotherNumberPart = tmp;
    }

    std::string unchangedPart = anotherNumberPart.substr(numberPart.size(),
                                                    anotherNumberPart.size() - numberPart.size());

    for (long i = numberPart.size() - 1; i >= 0; --i) {
        int tempResult = (numberPart[i] - 48) + (anotherNumberPart[i] - 48);

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            memory = true;
            tempResult -= 10;
        }

        fraction.push_back((char) (tempResult + 48));
    }

    reverse(fraction.begin(), fraction.end());
    fraction.append(unchangedPart);

    int i = fraction.size() - 1;
    while (fraction[i] == '0' && i >= 0) {
        fraction.pop_back();
        --i;
    }
}

void LargeNumber::sumIntegerParts(const LargeNumber &another, std::string &integer) {
    std::string numberPart, anotherNumberPart;
    getIntegerPart(numberPart);
    another.getIntegerPart(anotherNumberPart);

    // anotherNumber must be greater than number by length
    if (anotherNumberPart.size() < numberPart.size()) {
        std::string tmp = numberPart;
        numberPart = anotherNumberPart;
        anotherNumberPart = tmp;
    }

    int i = 0;
    while (i < numberPart.size()) {
        int tempResult = (numberPart[numberPart.size() - 1 - i] - 48) +
                         (anotherNumberPart[anotherNumberPart.size() - 1 - i] - 48);

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            tempResult -= 10;
            memory = true;
        }

        integer.push_back((char) (tempResult + 48));
        ++i;
    }

    while (i < anotherNumberPart.size()) {
        int tempResult = anotherNumberPart[anotherNumberPart.size() - 1 - i] - 48;

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            tempResult -= 10;
            memory = true;
        }

        integer.push_back((char) (tempResult + 48));
        ++i;
    }

    if (memory) {
        integer.push_back('1');
    }

    reverse(integer.begin(), integer.end());
}

void LargeNumber::additionImpl(const LargeNumber &another, LargeNumber &newNumber) {
    std::string fractionalPartResult, integerPartResult;
    sumFractionalParts(another, fractionalPartResult);
    sumIntegerParts(another, integerPartResult);

    // Create resulting string
    std::string result;
    result.append(integerPartResult);
    if (!fractionalPartResult.empty()) {
        result.append(".");
        result.append(fractionalPartResult);
    }

    newNumber.setNumber(result);
}

LargeNumber LargeNumber::operator+(const LargeNumber &anotherNumber) {
    // TODO: handle negative values
    LargeNumber sum("");
    additionImpl(anotherNumber, sum);

    return sum;
}

std::string LargeNumber::toString() const {
    return number;
}
