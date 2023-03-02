//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

std::string getDecimal(std::string binary, bool sign);

template<class T>
void getBinaryFromCoefficients(std::string &binary, const std::vector<T> &coefficients, bool sign);

// New API:

template<class T>
void getCoefficients(std::vector<T> &coefficients, std::string &decimal, bool sign);

template<class T>
void toTwosComplement(std::vector<T> &coefficients);

#endif //ND1_UTILS_H
