//
// Created by alexs on 2023-05-31.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, integral_multiplication) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "-1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "2.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-128.0"));
    EXPECT_EQ(number.toString(), "-256.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");
}

TEST(large_float, integral_with_float_multiplication) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("100.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.5"));
    EXPECT_EQ(number.toString(), "50.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.01"));
    EXPECT_EQ(number.toString(), "0.5");
}
