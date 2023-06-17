//
// Created by alexs on 2023-06-17.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, addition_basic) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("0.0");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.1");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("-0.2"));
    EXPECT_EQ(number.toString(), "-0.1");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.05"));
    EXPECT_EQ(number.toString(), "-0.05");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.05"));
    EXPECT_EQ(number.toString(), "0.0");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.5"));
    EXPECT_EQ(number.toString(), "0.5");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.25"));
    EXPECT_EQ(number.toString(), "0.75");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.125"));
    EXPECT_EQ(number.toString(), "0.875");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0625"));
    EXPECT_EQ(number.toString(), "0.9375");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("0.03125"));
    EXPECT_EQ(number.toString(), "0.96875");
}

TEST(large_float, large_numbers_addition) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("256.0");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>("65536.0"));
    EXPECT_EQ(number.toString(), "65792.0");

    number.add(LargeNumbers::LargeFloatImplementation<uint8_t>(
            "-4564152315458796846561315646876541521345648645321321545645231231545.165546876541231214564521321564532132"));
    EXPECT_EQ(number.toString(),
              "-4564152315458796846561315646876541521345648645321321545645231165753.165546876541231214564521321564532132");
}
