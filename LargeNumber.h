//
// Created by alexs on 2023-02-19.
//

#ifndef ND1_LARGENUMBER_H
#define ND1_LARGENUMBER_H

#include <string>

using namespace std;

struct SplittedNumber {
    string integerPart;
    string fractionalPart;
};

class LargeNumber {
private:
    string number;
    bool memory;

    // Function to add two positive numbers
    LargeNumber additionImpl(LargeNumber const &a, LargeNumber const &b);

    string sumFractionalParts(string a, string b);

    string sumIntegerParts(string a, string b);

    SplittedNumber split(const string &number);

public:
    LargeNumber(string number) : number(std::move(number)) {};

    LargeNumber operator+(LargeNumber const &anotherNumber);

    string toString();
};

#endif //ND1_LARGENUMBER_H
