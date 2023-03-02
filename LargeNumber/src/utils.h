//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

template<class T>
void getCoefficients(std::vector<T> &coefficients, std::string &decimal, bool sign);

template<class T>
void getDecimal(std::string &decimal, std::vector<T> coefficients, bool sign);

template<class T>
void toTwosComplement(std::vector<T> &coefficients);

template<class T>
void integerToCoefficients(std::vector<T> &coefficients, int number);

#endif //ND1_UTILS_H
