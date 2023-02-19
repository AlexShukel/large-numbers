//
// Created by alexs on 2023-02-19.
//

#include <algorithm>
#include "LargeNumber.h"

SplittedNumber LargeNumber::split(const string &number) {
    string integerPart, fractionalPart;
    bool isIntegerPart = true;

    for (auto c: number) {
        if (c == '.') {
            isIntegerPart = false;
        } else if (isIntegerPart) {
            integerPart.push_back(c);
        } else {
            fractionalPart.push_back(c);
        }
    }

    return {
            .integerPart = integerPart,
            .fractionalPart = fractionalPart
    };
}

string LargeNumber::sumFractionalParts(string a, string b) {
    string fractionalPartResult;

    // b must be greater than a by length
    if (a.length() > b.length()) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    string unchangedPart = b.substr(a.size(),
                                    b.size() - a.size());

    for (long i = a.size() - 1; i >= 0; --i) {
        int tempResult = (a[i] - 48) + (b[i] - 48);

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            memory = true;
            tempResult -= 10;
        }

        fractionalPartResult.push_back((char) (tempResult + 48));
    }

    reverse(fractionalPartResult.begin(), fractionalPartResult.end());
    fractionalPartResult.append(unchangedPart);

    int i = fractionalPartResult.size() - 1;
    while (fractionalPartResult[i] == '0' && i >= 0) {
        fractionalPartResult.pop_back();
        --i;
    }

    return fractionalPartResult;
}

string LargeNumber::sumIntegerParts(string a, string b) {
    string integerPartResult;

    // b must be greater than a by length
    if (b.size() < a.size()) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    int i = 0;
    while (i < a.size()) {
        int tempResult = (a[a.size() - 1 - i] - 48) +
                         (b[b.size() - 1 - i] - 48);

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            tempResult -= 10;
            memory = true;
        }

        integerPartResult.push_back((char) (tempResult + 48));
        ++i;
    }

    while (i < b.size()) {
        int tempResult = b[b.size() - 1 - i] - 48;

        if (memory) {
            ++tempResult;
            memory = false;
        }

        if (tempResult >= 10) {
            tempResult -= 10;
            memory = true;
        }

        integerPartResult.push_back((char) (tempResult + 48));
        ++i;
    }

    if (memory) {
        integerPartResult.push_back('1');
    }

    reverse(integerPartResult.begin(), integerPartResult.end());

    return integerPartResult;
}

LargeNumber LargeNumber::additionImpl(const LargeNumber &a, const LargeNumber &b) {
    SplittedNumber num1 = split(a.number);
    SplittedNumber num2 = split(b.number);

    string fractionalPartResult = sumFractionalParts(num1.fractionalPart, num2.fractionalPart);
    string integerPartResult = sumIntegerParts(num1.integerPart, num2.integerPart);

    // Create resulting string
    string result;
    result.append(integerPartResult);
    if (!fractionalPartResult.empty()) {
        result.append(".");
        result.append(fractionalPartResult);
    }

    LargeNumber newNumber(result);
    return newNumber;
}

LargeNumber LargeNumber::operator+(const LargeNumber &anotherNumber) {
    // TODO: handle negative values
    LargeNumber sum = additionImpl(number, anotherNumber);

    return sum;
}

string LargeNumber::toString() {
    return number;
}
