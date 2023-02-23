//
// Created by alexs on 2023-02-19.
//

#ifndef ND1_LARGENUMBER_H
#define ND1_LARGENUMBER_H

#include <string>

class LargeNumber {
private:
    std::string number;
    bool memory;

    void additionImpl(const LargeNumber &another, LargeNumber &newNumber);

    void sumFractionalParts(const LargeNumber &another, std::string &fraction);

    void sumIntegerParts(const LargeNumber &another, std::string &integer);

    void getFractionalPart(std::string &fraction) const;

    void getIntegerPart(std::string &integer) const;

public:
    LargeNumber(std::string number) : number(std::move(number)) {};

    LargeNumber operator+(LargeNumber const &anotherNumber);

    void setNumber(std::string &newNumber) {
        number = newNumber;
    }

    std::string toString() const;
};

#endif //ND1_LARGENUMBER_H
