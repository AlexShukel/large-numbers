//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_CONFIG_H
#define ND1_CONFIG_H

#include <cstdint>

namespace LargeNumbers {
    // The type of stored coefficient. For debugging it is 8 bites. For final result - 32 bits.
    using CoefficientType = uint8_t;
    using exponent_type = int32_t;
}

#endif //ND1_CONFIG_H
