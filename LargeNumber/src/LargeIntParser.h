//
// Created by alexs on 2023-03-04.
//

#ifndef ND1_LARGEINTPARSER_H
#define ND1_LARGEINTPARSER_H

#include <string>
#include <vector>

template<class T>
class LargeIntParser {
private:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;

    static void coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients);

public:
    static void toTwosComplement(std::vector<T> &coefficients);

    static std::string toString(std::vector<T> coefficients, bool sign);

    static void fromString(std::vector<T> &coefficients, bool &sign, const std::string &number);

    static void fromInteger(std::vector<T> &coefficients, bool &sign, int number);
};


#endif //ND1_LARGEINTPARSER_H
