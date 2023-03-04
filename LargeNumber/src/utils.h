//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <tuple>
#include "LargeNumbers.h"
#include "config.h"

template<class T>
class LargeIntUtils {
private:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;

    static void coefficientsToBinary(std::string &binary, const std::vector<T> &coefficients);

public:
    static void toTwosComplement(std::vector<T> &coefficients);

    static void integerToCoefficients(std::vector<T> &coefficients, int number);

    static void getDecimal(std::string &decimal, std::vector<T> coefficients, bool sign);

    static void getCoefficients(std::vector<T> &coefficients, std::string decimal, bool sign);
};

template<class T>
class LargeDoubleUtils {
public:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
    static const int PRECISION = 332.1928094887362347870 / COEFFICIENT_BIT_SIZE;

    // Return a mantissa, exponent and sign of parsed double
    static std::tuple<LargeIntMath<T>, exponent_type, bool> parseLargeDouble(const std::string &number);

    static void getFractionCoefficients(std::vector<T> &coefficients, std::string fraction);
};

#endif //ND1_UTILS_H
