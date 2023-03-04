//
// Created by alexs on 2023-03-03.
//

#include "LargeDoubleMath.h"
#include "../utils.h"
#include <regex>
#include <tuple>

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(): mantissa(LargeIntMath<T>()), exponent(0), sign(false) {}

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(LargeIntMath<T> mantissa, exponent_type exponent, bool sign): mantissa(mantissa),
                                                                                                  exponent(exponent),
                                                                                                  sign(sign) {}

template<class T>
LargeDoubleMath<T>::LargeDoubleMath(const std::string &number) {
    if (!std::regex_match(number, std::regex("^-?\\d+\\.\\d+$"))) {
        throw std::invalid_argument("LargeDouble validation error: number does not match format (<digits>.<digits>).");
    }

    auto parsedNumber = LargeDoubleUtils<T>::parseLargeDouble(number);

    mantissa = std::get<0>(parsedNumber);
    exponent = std::get<1>(parsedNumber);
    sign = std::get<2>(parsedNumber);
}

template
class LargeDoubleMath<uint8_t>;

template
class LargeDoubleMath<uint32_t>;
