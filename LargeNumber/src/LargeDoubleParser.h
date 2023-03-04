//
// Created by alexs on 2023-03-04.
//

#ifndef ND1_LARGEDOUBLEPARSER_H
#define ND1_LARGEDOUBLEPARSER_H

#include <string>
#include "LargeDoubleMath.h"
#include "LargeIntMath.h"
#include "config.h"

template<class T>
class LargeDoubleParser {
private:
    static constexpr size_t COEFFICIENT_BIT_SIZE = sizeof(T) * 8;
    static constexpr size_t PRECISION = 332.1928094887362347870 / COEFFICIENT_BIT_SIZE;

public:
    static size_t getPrecision();

    static LargeDoubleMath<T> parse(std::string source);

    static void getFractionCoefficients(std::vector<T> &coefficients, std::string fraction);
};


#endif //ND1_LARGEDOUBLEPARSER_H
