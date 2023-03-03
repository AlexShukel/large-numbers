//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

template<class T>
class LargeIntUtils {
private:
    static void coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients);

public:
    static void toTwosComplement(std::vector<T> &coefficients);

    static void integerToCoefficients(std::vector<T> &coefficients, int number);

    static void getDecimal(std::string &decimal, std::vector<T> coefficients, bool sign);

    static void getCoefficients(std::vector<T> &coefficients, std::string decimal, bool sign);
};

#endif //ND1_UTILS_H
