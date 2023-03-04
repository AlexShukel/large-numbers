//
// Created by alexs on 2023-03-04.
//

#ifndef ND1_LARGEDOUBLEPARSER_H
#define ND1_LARGEDOUBLEPARSER_H

#include <string>
#include "LargeIntMath.h"
#include "config.h"

template<class T>
class LargeDoubleParser {
private:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
    static const int PRECISION = 332.1928094887362347870 / COEFFICIENT_BIT_SIZE;

    static void getFractionCoefficients(std::vector<T> &coefficients, std::string fraction);

public:
    static void fromString(LargeIntMath<T> &mantissa, exponent_type &exponent, bool &sign, std::string number);

    static std::string toString(const LargeIntMath<T> &mantissa, const exponent_type &exponent, const bool &sign);
};


#endif //ND1_LARGEDOUBLEPARSER_H
