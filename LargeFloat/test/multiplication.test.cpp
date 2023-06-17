//
// Created by Aleksandras on 2023-06-15.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, multiplication_zero) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-0.1"));
    EXPECT_EQ(number.toString(), "0.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("1.0");
    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0");
    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");
}

TEST(large_float, multiplication_without_fraction) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "-1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("2.0"));
    EXPECT_EQ(number.toString(), "2.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-4.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("2.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("256.0"));
    EXPECT_EQ(number.toString(), "512.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-1024.0");
}

TEST(large_float, multiplication_with_fraction) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("0.1");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.01");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.01"));
    EXPECT_EQ(number.toString(), "0.0001");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("10000.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0625"));
    EXPECT_EQ(number.toString(), "0.0625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0625"));
    EXPECT_EQ(number.toString(), "0.00390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.000390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("10.0"));
    EXPECT_EQ(number.toString(), "0.00390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-0.0078125");
}

TEST(large_float, multiplication_mixed) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("1.1");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.1"));
    EXPECT_EQ(number.toString(), "1.21");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.223"));
    EXPECT_EQ(number.toString(), "-2.68983");
}

TEST(large_float, multiplication_large_numbers) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("456486768454531453453.456465415416453123");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("7874654153412.146551534564"));
    EXPECT_EQ(number.toString(), "3594675427188164949046079279342197.315943069945180624309620243372");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");
}

TEST(large_float, multiplication_stress_test) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number(
            "83957209573290750932672903672903804891782184018250185601286.65823579237639207693267290672390673296723906");

    LargeNumbers::LargeFloatImplementation<uint8_t> number2(
            "0.000000000000000000000000000057281572937653276930262869030632626000603602306023060234274923789048329054832580923589032568932686005");

    EXPECT_EQ(number.toString(),
              "83957209573290750932672903672903804891782184018250185601286.65823579237639207693267290672390673296723906");
    EXPECT_EQ(number2.toString(),
              "0.000000000000000000000000000057281572937653276930262869030632626000603602306023060234274923789048329054832580923589032568932686005");

    number.multiply(number2);

    EXPECT_EQ(number.toString(),
              "4809201023814296104800879450164.856849018891609004588628065474914598736529749743323350577001026205656903849007272826405795410130297");
}
