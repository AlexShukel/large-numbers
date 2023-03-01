//
// Created by alexs on 2023-02-26.
//

#ifndef ND1_UTILS_H
#define ND1_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

std::string getBinary(std::string decimal);

std::string getDecimal(std::string binary, bool sign);

template<class T>
void getBinaryFromCoefficients(std::string &binary, const std::vector<T> &coefficients, bool sign);

template<typename T>
void getCoefficientsFromBinary(std::vector<T> &coefficients, const std::string &binary, bool sign);

#endif //ND1_UTILS_H
